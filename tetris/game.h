#ifndef GAME_H
#define GAME_H

#include<SFML/Graphics.hpp>
#include<vector>
#include<iostream>

#include "./myutility/MyUtility.h"
#include "grid.h"
namespace tetris
{
    class Game
    {
    protected:
        sf::RenderWindow window;//The window
        sf::RectangleShape block;//The base single block
        sf::Vector2<int> currentMove, currentPosition, gridSize;//Current move, position and the grid size.
        std::vector<std::vector<sf::RectangleShape*> > currentBlock;//Current multiple-blocks being used.
        unsigned int currentBlockType, currentBlockState;//variables holding block type and block state.
        mu::MyRandom myRandom;//My random class declaration.
        tetris::Grid grid;//Grid class declaration.
        //Total frames timer, update frames timer, ect...
        mu::MyTime totalFrames, updateFrames, drawFrames, fallFrames, flipFrames, forceFrames;
        //Force frame created to not reset every second even if not in use.

        sf::Text text;//Base text for program declared.
        sf::Font font;//Base font for program declared.
        bool forceFall;//Forcefall boolean: true if user pressed up. Else false. Accessed in event loop.

        void setPrint();//Setup the print for score display.
        void printScore(sf::RenderWindow &window);//Print the score
        void selectBlockVariations();//Selects the blocks variations.
        void checkMove();//Event check for movements.
        void createBlock();//Creates new Blocks if current block is empty : (blocks is an array of (another array) of blocks.
        void flipBlock(int value);//Attempts to flip the blocks
        void events();//The events function: should hold all of the event procedures in the main-loop.
        void updates();//The updates function: should hold all of the updates procedures in the main-loop.
        bool tryMove(sf::Vector2<int> newMove = sf::Vector2<int>());//Try to move the block method.
        void fall(bool force = false);//The fall function: executes the Tetris fall procedure. This process will attempt to bind the block into the grid space and cleanup.
        void draw();//The draw function: executes all needed to be drawn functions from game class and grid class.
        void setup();//This function holds the default setups for the window and timers.
    public:
        Game(sf::Vector2i gridSize = sf::Vector2i(10,24), bool running = true);//Initializes grid and calls run.
        ~Game();//Prints score to the console on close/gameOver.
        void run();//This is the run method. Calling this window will create a playable game. Not thread-able: one window only.
    };
}
#endif // GAME_H
