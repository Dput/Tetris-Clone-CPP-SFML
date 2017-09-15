#Simple MAKEFILE to build the Tetris Clone game.
#Can possibly work with both Linux and window with some minor changes.

#Windows cannot access the 'rm',the delete function in the target clean, outside of msys so you'll need gnu-make and msys installed.
#	Afterwards you can either run this makefile in the msys shell or if you have both msys and gnu-make in the windows path you can call
#	'make' at the cmdpromt in this directory to create the executable.
#	Make sure to adjust the SFMLINCLUDES and SFMLLIBPATH path to your own, you must have SFML installed to compile this.
#
#	Warning! If you've added msys to your windows path, note that cmake projects usually do not like this
#		so removing msys from the windows path is expected after compiling this project.
#		If you choose to leave msys in the path, just know that cmake may inform you of an error if you're
#		using cmake with "sh.exe". It'll tell you if you read.

#It code should work with linux with a bit of fixing. SFMLINCLUDES is pointing to a windows path, change it to the appropriate linux path of SFML's INCLUDE FILES.
#	The SFMLLIBPATH will also need to be redirected to the appropriate path.

CXX					= g++ -std=c++14
CXXFLAGS			= -w

####################These should be adjusted to fit your NEEDS####################
#The First one is the SFML include path:
SFMLINCLUDES		= -I C:/SFML-2.4.2/include
#The Second one is the SFML lib path:
SFMLLIBPATH			= -L C:/SFML-2.4.2/lib
##################################################################################

SFMLLIB				= -lsfml-graphics -lsfml-window -lsfml-system

GAMELIBPATH			= tetris
UTILITYLIBPATH		= tetris/myutility

OBJS				= main.o game.o grid.o myrandom.o mytime.o myinput.o
EXE					= main.exe

main.exe:			$(OBJS)
					$(CXX) -o $(EXE) $(CXXFLAGS) $(OBJS) $(SFMLINCLUDES) $(SFMLLIBPATH) $(SFMLLIB)
main.o:				main.cpp
					$(CXX) -c main.cpp $(CXXFLAGS) $(SFMLINCLUDES) $(SFMLLIBPATH) $(SFMLLIB)
game.o:				$(GAMELIBPATH)/game.cpp $(GAMELIBPATH)/grid.h
					$(CXX) -c $(GAMELIBPATH)/game.cpp $(CXXFLAGS) $(SFMLINCLUDES) $(SFMLLIBPATH) $(SFMLLIB)
grid.o:				$(GAMELIBPATH)/grid.cpp
					$(CXX) -c $(GAMELIBPATH)/grid.cpp $(CXXFLAGS) $(SFMLINCLUDES) $(SFMLLIBPATH) $(SFMLLIB)
myinput.o:			$(UTILITYLIBPATH)/myinput.cpp
					$(CXX) -c $(UTILITYLIBPATH)/myinput.cpp $(CXXFLAGS) $(SFMLINCLUDES) $(SFMLLIBPATH) $(SFMLLIB)
myrandom.o:			$(UTILITYLIBPATH)/myrandom.cpp
					$(CXX) -c $(UTILITYLIBPATH)/myrandom.cpp
mytime.o:			$(UTILITYLIBPATH)/mytime.cpp
					$(CXX) -c $(UTILITYLIBPATH)/mytime.cpp $(CXXFLAGS) $(SFMLINCLUDES) $(SFMLLIBPATH) $(SFMLLIB)

.PHONY:				clean
#Clean requires msys, else physically delete the object files yourself.
clean:				
					rm $(EXE) $(OBJS)
