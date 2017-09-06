#ifndef SERVER_H
#define SERVER_H
#include <SFML/Network/UdpSocket.hpp>
#include <mutex>
/* Simple Server class: Automated client manager, reader, writer, and a send function.
    Connect clients to the server by manually adding ips and ports
        addClient(ip,port) manually adds a client.
        Usage Note: can still receive non-client messages.
    read strings from the server with read and readAll
        read() returns the oldest string remaining in server, and deletes it from server log.
        readAll() return a vector of all strings in server, and clears server log.
    write strings to the server with write
        write(std::string) sends a single string to all clients on the server.
        write(std::vector<std::string>) sends a vector of strings to all clients on the server.
    send a string to a target(Ip address, port)
        This will enable you to establish new connections.
*/
namespace mu
{
    class MyServer
    {
    private:
    protected:
        sf::UdpSocket socket;                               //A UDP socket for connection
        unsigned short portNumber, serverPortNumber;        //Our port number and the servers port number.
        std::vector<sf::IpAddress> clientIpAddress;         //The clients IPs to broadcast to.
        sf::IpAddress server;                               //The servers(targeted hosts) IP.
        std::vector<unsigned int> clientPort;               //The clients ports to broadcast to.

        //Mutexs are locks to enable multi thread and associates with implied names.
        std::mutex runMutex, clientMutex, readDataMutex, serverMutex, writeDataMutex, passwordMutex, portMutex;

        //running controls if the server is up, servering controls if the server is hosting.
        bool running, servering;

        //ReadData stores the received strings, writeData stores the strings to be sent.
        std::vector<std::string> readData, writeData;

        /*Protected Methods*/
        //Is running checks if the server is still running, is server checks if this server is a client or server.
        bool isRunning();
        bool isServer();

        //ReadNetwork gets incoming strings and stores it in readData, writeNetwork takes strings from writeData and sends it to users.
        void readNetwork();
        void writeNetwork();
    public:
        /*Public Methods*/
        MyServer(bool servering = false, unsigned short portNumber = 11235);//Initial
        void setup(bool servering = false, unsigned short portNumber = 11235);//Setup

        ~MyServer();

        void run();//Activate server
        void shutdown();//De-activate server

        void changePort(unsigned short newPort);//Changes our port

        void runStatusChange(bool status);//Changes run status
        void serverStatusChange(bool status);//Changes server status (on/off);

        bool write(std::vector<std::string> data);//Sends a vector of string to the clients
        bool write(std::string data);//Sends a single string to the clients

        std::vector<std::vector<std::string> > readAll();//Read all strings from this server
        std::vector<std::string> read();//Read oldest string on this server.

        bool addClient(sf::IpAddress ipAddress, unsigned short port);//Add a client to the client table.
        bool setServer(std::string ip);//Set a host server.

        bool send(std::string str, sf::IpAddress ip, unsigned short port);//Send a manual single string
    };
}
#endif // SERVER_H
