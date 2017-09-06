#include "myserver.h"
#include <SFML/Network/Packet.hpp>
#include <SFML/System/Sleep.hpp>
#include <iostream>
#include <thread>
bool mu::MyServer::isRunning()
{
    bool runner = true;//Automatically assume running
    if(runMutex.try_lock())
    {
        runner = running;
        runMutex.unlock();
    }
    return runner;
}
bool mu::MyServer::isServer()
{
    bool serving = false;
    if(serverMutex.try_lock())
    {
        serving = this->servering;
        serverMutex.unlock();
    }
    return serving;
}
void mu::MyServer::readNetwork()//Use a thread of this to read Data from network and store it in readData.
{
    while(isRunning())
    {
        sf::Packet packet;//An empty packet.
        sf::IpAddress ipAddress;//Empty address
        unsigned short port = 11235;//default port 11235
        socket.receive(packet,ipAddress,port);//Blocking is off, attempt to receive data.

        if(packet.getDataSize()>0)//Only bother locking if any data received.
        {
            std::string temp;
            readDataMutex.lock();/* !Code is locked in data access! Will wait */
            while(packet >> temp)//Attempt to get any data from packet, if any.
            {
                readData.push_back(temp);//Accumulates, not overwrite.
                temp = "";
            }
            readDataMutex.unlock();/* !data lock is freed now! */
        }
        sf::sleep(sf::milliseconds(1000/240));
    }
    std::cout<<"readNetwork() has ended safely\n";
}
void mu::MyServer::writeNetwork()//Use a thread of this to send Data to network that were stored in writeData.
{
    while(isRunning())
    {
        if(writeDataMutex.try_lock())//Attempt to lock write writeData to send.
        {
            if(isServer())
            {//Send data too all clients
                if(clientMutex.try_lock())//Attempt to lock the client for use. Outside of loops for one time lock.
                {
                    for(auto i = 0; i < writeData.size(); ++i)//For every writeData to be written
                    {
                        for(auto j = 0; j < clientIpAddress.size(); ++j)//send to every client
                        {
                            sf::Packet packet;
                            if(writeData[i].find(clientIpAddress[j].toString()) != std::string::npos)
                            {
                                packet << writeData[i];
                                socket.send(packet,clientIpAddress[j],clientPort[j]);//SFML UDPsocket (packet,remoteIP,remotePort).
                            }
                        }
                    }
                    writeData.clear();//Clears the buffer after use.
                    clientMutex.unlock();//Must be embedded in a clients lock method.
                }
            }
            else
            {//Send data to server
                if(serverMutex.try_lock())
                {
                    if(server != sf::IpAddress::None)
                    {
                        for(auto i = 0; i < writeData.size(); ++i)//For every writeData to be written
                        {
                            sf::Packet packet;
                            packet << writeData[i];
                            //EDIT: Non blocking, hopefully no problems. otherwise mutex it.
                            socket.send(packet,server,serverPortNumber);//SFML UDPsocket (packet,remoteIP,remotePort).
                        }
                    }
                }
            }
            writeDataMutex.unlock();
        }
        sf::sleep(sf::milliseconds(1000/240));
    }
    std::cout<<"writeNetwork() has ended safely\n";
}
mu::MyServer::MyServer(bool servering, unsigned short portNumber)
{
    setup(servering,portNumber);
}
void mu::MyServer::setup(bool servering, unsigned short portNumber)
{
    socket.bind(portNumber);
    socket.setBlocking(false);

    this->runStatusChange(true);
    this->serverStatusChange(servering);
    this->changePort(portNumber);
    run();
}
mu::MyServer::~MyServer()
{
    shutdown();//shutdown if not already shutdown.
}
void mu::MyServer::run()
{
    std::thread readThread(&MyServer::readNetwork,this), writeThread(&MyServer::writeNetwork,this);
    readThread.detach();
    writeThread.detach();
}
void mu::MyServer::shutdown()
{
    runMutex.lock();
        running = false;
    runMutex.unlock();
    if(isServer())
    {
        serverStatusChange(false);
    }
}
void mu::MyServer::changePort(unsigned short newPort)
{
    portMutex.lock();
    this->portNumber = newPort;
    portMutex.unlock();

}
void mu::MyServer::runStatusChange(bool status)
{
    runMutex.lock();
    running = status;
    runMutex.unlock();
}
void mu::MyServer::serverStatusChange(bool status)
{
    serverMutex.lock();
    servering = status;
    serverMutex.unlock();
}
bool mu::MyServer::write(std::vector<std::string> data)//Backup data, if false, data should not be deleted.
{
    //TODO: use to send data, since it will be read in updateNetwork.
    if(writeDataMutex.try_lock())
    {
        for(auto i = 0; i < data.size(); ++i)
        {
            this->writeData.insert(this->writeData.end(),sf::IpAddress::getLocalAddress().toString()+";"+std::to_string(portNumber)+";"+data[i]);//APPEND
        }
        //Inserted data is automatically used in the updateNetwork method.
        writeDataMutex.unlock();
        return true;
    }
    return false;
}
bool mu::MyServer::write(std::string data)
{
    if(writeDataMutex.try_lock())
    {
        this->writeData.insert(this->writeData.end(),sf::IpAddress::getLocalAddress().toString()+";"+std::to_string(portNumber)+";"+data);
        writeDataMutex.unlock();
        return true;
    }
    return false;
}
std::vector<std::vector<std::string> > mu::MyServer::readAll()
{
    std::vector<std::vector<std::string> > returnData;
    if(readDataMutex.try_lock())
    {
        while(readData.size()>0)
        {
            returnData.push_back(read());
        }
        readDataMutex.unlock();
    }
    return returnData;
}
bool mu::MyServer::addClient(sf::IpAddress ipAddress, unsigned short port)//Add client Ip and port to tables.
{
    unsigned int retries = 0;
    if(isServer())
    {
        do
        {
            if(clientMutex.try_lock())
            {
                clientIpAddress.push_back(ipAddress);
                clientPort.push_back(port);
                clientMutex.unlock();
                return true;
            }
            sf::sleep(sf::milliseconds(1000/480));
        }while(++retries < 10);//Retry 10 times
    }
    return false;
}
std::vector<std::string> mu::MyServer::read()
{
    std::vector<std::string> returnData;
    if(readDataMutex.try_lock())
    {
        if(readData.size() > 0)
        {
            while(readData[0].find(";") != std::string::npos)
            {
                returnData.push_back(readData[0].substr(0,readData[0].find(";")));
                readData[0] = readData[0].substr(readData[0].find(";")+1,readData[0].size());
            }
            returnData.push_back(readData[0]);
            readData.erase(readData.begin());
        }
        readDataMutex.unlock();
    }
    return returnData;
}
bool mu::MyServer::setServer(std::string ip)
{
    unsigned int retries = 0;
    if(!isServer())
    {
        do
        {
            if(serverMutex.try_lock())
            {
                server = sf::IpAddress(ip);
                serverMutex.unlock();
            }
            sf::sleep(sf::milliseconds(1000/480));
        }while(++retries < 10);//Retry 10 times
    }
    return false;
}
bool mu::MyServer::send(std::string str, sf::IpAddress ip, unsigned short port)
{
    sf::Packet packet;
    packet<<str;
    socket.send(packet,ip,port);
}
