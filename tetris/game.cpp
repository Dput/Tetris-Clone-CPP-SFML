#include "game.h"

void tetris::Game::setPrint()//Setup the print for score display.
{
    font.loadFromFile("DroidSansMono.ttf");//Load font from file.
    text.setFont(font);//Load font into text object.
    text.setCharacterSize(12);//Setup text objects font size.
    text.setFillColor(sf::Color(255,255,255,255));//Set text object font color.
}
void tetris::Game::printScore(sf::RenderWindow &window)//Print the score
{
    text.setPosition({0,gridSize.y*grid.blockSize});//Positioned far left(x) and after the grid(y).
    text.setString("Total Score: "+std::to_string(grid.totalScore));//Set text to be printed.
    window.draw(text);//draw text
}
void tetris::Game::selectBlockVariations()//Selects the blocks variations.
{
        //Configure block arrangements for current block type.
        //ALL BLOCKS HARD CODED TO SAVE PROCESSING TIME(S).
        //&block is a pointer to the current block being used.
        switch(currentBlockType)
        {
        case 0://Line
            currentBlockState%=2;
            if(currentBlockState==0)
            {
                currentBlock =
                {
                    {0,0,0,0},
                    {&block,&block,&block,&block},
                    {0,0,0,0},
                    {0,0,0,0},
                };
            }
            else
            {
                currentBlock =
                {
                    {0,&block,0,0},
                    {0,&block,0,0},
                    {0,&block,0,0},
                    {0,&block,0,0},
                };
            }
            break;
        case 1://Square
            currentBlockState%=1;
            currentBlock =
            {
                {&block,&block,0,0},
                {&block,&block,0,0},
                {0,0,0,0},
                {0,0,0,0},
            };
            break;
        case 2://T-shape
            currentBlockState%=4;
            if(currentBlockState==0)
            {
                currentBlock =
                {
                    {0,&block,0,0},
                    {&block,&block,&block,0},
                    {0,0,0,0},
                    {0,0,0,0},
                };
            }
            else if(currentBlockState==1)
            {
                currentBlock =
                {
                    {0,&block,0,0},
                    {&block,&block,0,0},
                    {0,&block,0,0},
                    {0,0,0,0},
                };
            }
            else if(currentBlockState==2)
            {
                currentBlock =
                {
                    {0,0,0,0},
                    {&block,&block,&block,0},
                    {0,&block,0,0},
                    {0,0,0,0},
                };
            }
            else if(currentBlockState==3)
            {
                currentBlock =
                {
                    {0,&block,0,0},
                    {0,&block,&block,0},
                    {0,&block,0,0},
                    {0,0,0,0},
                };
            }
            break;
        case 3://S-shape
            currentBlockState%=2;
            if(currentBlockState==0)
            {
                currentBlock =
                {
                    {0,&block,&block,0},
                    {&block,&block,0,0},
                    {0,0,0,0},
                    {0,0,0,0},
                };
            }
            else
            {
                currentBlock =
                {
                    {0,&block,0,0},
                    {0,&block,&block,0},
                    {0,0,&block,0},
                    {0,0,0,0},
                };
            }
            break;
        case 4://Z-shape
            currentBlockState%=2;
            if(currentBlockState==0)
            {
                currentBlock =
                {
                    {&block,&block,0,0},
                    {0,&block,&block,0},
                    {0,0,0,0},
                    {0,0,0,0},
                };
            }
            else
            {
                currentBlock =
                {
                    {0,0,&block,0},
                    {0,&block,&block,0},
                    {0,&block,0,0},
                    {0,0,0,0},
                };
            }
            break;
        case 5://L-shape
            currentBlockState%=4;
            if(currentBlockState==0)
            {
                currentBlock =
                {
                    {&block,0,0,0},
                    {&block,&block,&block,0},
                    {0,0,0,0},
                    {0,0,0,0},
                };
            }
            else if(currentBlockState==1)
            {
                currentBlock =
                {
                    {0,&block,&block,0},
                    {0,&block,0,0},
                    {0,&block,0,0},
                    {0,0,0,0},
                };
            }
            else if(currentBlockState==2)
            {
                currentBlock =
                {
                    {0,0,0,0},
                    {&block,&block,&block,0},
                    {0,0,&block,0},
                    {0,0,0,0},
                };
            }
            else if(currentBlockState==3)
            {
                currentBlock =
                {
                    {0,&block,0,0},
                    {0,&block,0,0},
                    {&block,&block,0,0},
                    {0,0,0,0},
                };
            }
            break;
        case 6://Reverse L-shape
            currentBlockState%=4;
            if(currentBlockState==0)
            {
                currentBlock =
                {
                    {0,0,0,0},
                    {&block,&block,&block,0},
                    {&block,0,0,0},
                    {0,0,0,0},
                };
            }
            else if(currentBlockState==1)
            {
                currentBlock =
                {
                    {&block,&block,0,0},
                    {0,&block,0,0},
                    {0,&block,0,0},
                    {0,0,0,0},
                };
            }
            else if(currentBlockState==2)
            {
                currentBlock =
                {
                    {0,0,&block,0},
                    {&block,&block,&block,0},
                    {0,0,0,0},
                    {0,0,0,0},
                };
            }
            else if(currentBlockState==3)
            {
                currentBlock =
                {
                    {0,&block,0,0},
                    {0,&block,0,0},
                    {0,&block,&block,0},
                    {0,0,0,0},
                };
            }
            break;
        }
}
void tetris::Game::checkMove()//Event check for movements.
{
    const static sf::Vector2i defaultMovement;
    currentMove = defaultMovement;//Reset Block movement.

    std::vector<int> keysPressed = mu::MyInput::keyboard();//get keys pressed as a vector from myInput::keyboard().

    for(auto i = 0; i < keysPressed.size(); ++i)
    {
        switch(sf::Keyboard::Key(keysPressed[i]))
        {
            case sf::Keyboard::Key::Up:
                forceFall = true;
                break;
            case sf::Keyboard::Key::Down:
                ++currentMove.y;
                break;
            case sf::Keyboard::Key::Left:
                --currentMove.x;
                break;
            case sf::Keyboard::Key::Right:
                ++currentMove.x;
                break;
            case sf::Keyboard::Key::X:
                if(flipFrames.check())
                {
                    flipBlock(1);
                    //Partial time is carried over so reset.
                    flipFrames.reset();
                }
                break;
            case sf::Keyboard::Key::Z:
                if(flipFrames.check())
                {
                    flipBlock(-1);
                    //Partial time is carried over so reset.
                    flipFrames.reset();
                }
                break;
            case sf::Keyboard::Key::S:
                if(swapFrames.check())
                {
                    swapBlock();
                    swapFrames.reset();
                }
                break;
            case sf::Keyboard::Key::A:
                if(swapFrames.check())
                {
                    swapBlock();
                    swapFrames.reset();
                }
                break;
        }
    }
}
void tetris::Game::createBlock()//Creates new Blocks if current block is empty : (blocks is an array of (another array) of blocks.
{
    if(currentBlock.size()<1)//Will only work if we do not have a block (not a single node).
    {
        //Choose a color for the current block.
        block.setFillColor(sf::Color(myRandom.get(155,255),myRandom.get(155,255),myRandom.get(155,255)));

        //Choose a type of block for current block
        currentBlockType = myRandom.get(0,6);

        //Choose a state of block for current block
        currentBlockState = myRandom.get(0,4);

        //Select Block variations:
        selectBlockVariations();
    }
}
void tetris::Game::flipBlock(int value)//Attempts to flip the blocks
{
    if(currentBlock.size()>0)//Only work if we have a block with size > 0;
    {
        unsigned int tempBlockState = currentBlockState;
        int adjustmentPos = 0;
        if(value<0)
            value = 3;
        currentBlockState+=value;
        selectBlockVariations();
        //Check grid for fitness, if not fit, enter loop for correction/undo any changes.
        if(!grid.check(currentPosition,currentBlock))
        {
            //Check again if the current block is outside of game zone (less 4, greater than 6).
            while(currentPosition.x + adjustmentPos < (int)currentBlock.size() ||
                  currentPosition.x + adjustmentPos > gridSize.x - (int)currentBlock.size())
            {
                if(currentPosition.x + adjustmentPos < (int)currentBlock.size())
                {
                    //Try a larger position, increment adjustment X.
                    ++adjustmentPos;
                }
                if(currentPosition.x + adjustmentPos > gridSize.x - (int)currentBlock.size())
                {
                    //Try a smaller position, decrement adjustment X.
                    --adjustmentPos;
                }
                if(grid.check(currentPosition+sf::Vector2<int>(adjustmentPos,0),currentBlock))
                {
                    //Good update adjustments and exit method.
                    currentPosition.x += adjustmentPos;
                    return;
                }
            }
            //Bad, reset block state, and rebuild previous block with block variations method.
            currentBlockState = tempBlockState;//Reset state.
            selectBlockVariations();//Find associated block formation.
            return;
        }
    }
}
void tetris::Game::events()//The events function: should hold all of the event procedures in the main-loop.
{
    //Event loop runs continuously, and only sleep a tiny bit of milliseconds from the game::run() game loop.
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)//Close window if user clicks X.
            window.close();
    }
    checkMove();//detectKeyboardInput();
}
void tetris::Game::updates()//The updates function: should hold all of the updates procedures in the main-loop.
{
    if(updateFrames.check())
    {
        //Allows users force fall blocks every forceFrame.
        if(forceFall && forceFrames.check())
        {
            while(tryMove(sf::Vector2i(0,1)));
            fall(true);
            forceFrames.reset();//Reset forceFrame, to make equal gaps in every fall.
            fallFrames.reset();//Reset fallFrames to disable a fall, since we've already done a forceDrop.
        }
        else
        {
            if(!tryMove(currentMove))//Try to do a normal move.
            {
                //If no good, also check if it's able to move down, if moving down.
                if(currentMove.y > 0)//Test if the user wanted to try to move down.
                {
                    tryMove(sf::Vector2<int>(0,currentMove.y));//Try to just move down, applicable from above test.
                }
            }
        }
        forceFall = false;//Reset forceFall, even if not used. It is modified in events game::method.
    }
}
bool tetris::Game::tryMove(sf::Vector2<int> newMove)
{
    sf::Vector2<int> tempPosition = currentPosition;//Copy position for use.
    tempPosition += newMove;//Add newMove with current position. MODIFIY change.

    //check if coordinates are valid with grid
    if(grid.check(tempPosition,currentBlock))//Test if new Position is valid.
    {
        currentPosition = tempPosition;//Apply the modified change if valid: update position.
        if(newMove.y != 0)
        {
            fallFrames.reset();
        }
        return true;
    }
    return false;
}
void tetris::Game::fall(bool force)//The fall function: executes the Tetris fall procedure. This process will attempt to bind the block into the grid space and cleanup.
{
    if(fallFrames.check() || force)//Check fall timer, if ready to fall, or if force fall.
    {
        if(currentBlock.size()>0)//Only relevant if we have a Current block with a size > 0.
        {
            if(!tryMove(sf::Vector2<int>(0,1)))//Try to move down.
            {
                //Try to insert block to grid, fail = game over.
                if(grid.insert(currentPosition,currentBlock))
                {
                    window.close();//Close the window. We couldn't move, nor could we bind the block into the grid.
                }

                //Assuming not gameOver, so cleaning up and refreshing blocks and position.
                grid.cleanup();//Use the grids cleanup method: Basic Tetris effect and stuff.
                currentBlock.clear();//Clear our pointers to the block. It's in the hands of the grid now.
                currentPosition = sf::Vector2<int>(myRandom.get(1,gridSize.x-5),0);//Reset current block position to random.
                swapBool = true;//Allow swap again. Once per block.
                createBlock();
            }
        }
    }
}
void tetris::Game::draw()//The draw function: executes all needed to be drawn functions from game class and grid class.
{
    //Simple draw function.

    if(drawFrames.check())//Checks draw timer: 60fps: set in setup game::setup() method.
    {
        window.clear();//SFML clear screen with default black. Acceptable parameters of sf::Color("A color");
        grid.draw(window);//Access grids draw function, passing it the window for access to windows draw.
        if(currentBlock.size()>0)//Only do if current block is valid.
        {
            grid.draw(window,currentBlock,currentPosition);
        }
        printScore(window);//Draws score to bottom left corner.
        window.display();//Displays all drawings onto the window.
    }
}
void tetris::Game::setup()//This function holds the default setups for the window and timers.
{
    //Setup Window, times and print.
    window.create(sf::VideoMode(gridSize.x*25, (gridSize.y+1)*25), "SFML works!");//Extra 1 space(y) for score(bottom).

    //Reset a particular settings of a timer to ? actions per second, where ? = the argument being passed.
    totalFrames.reset(120);//Reset timer object for total to ? actions per second.
    updateFrames.reset(10);//Reset timer object for update to ? actions per second.
    drawFrames.reset(60);//Reset timer object for draw to ? action per second.
    fallFrames.reset(1);//Reset timer object for fall to ? action per second.
    flipFrames.reset(5);//Reset timer object for flip to ? action per second.
    forceFrames.reset(2);//Reset timer object for forceFall to ? actions per second.
    swapFrames.reset(1);//Resets timer for swapFrame.

    setPrint();
    currentPosition = sf::Vector2<int>(myRandom.get(1,gridSize.x-5),0);
    forceFall = false;
    swapBool = true;
    createBlock();
}
void tetris::Game::resetTimers()
{
    //Reset all times:
    totalFrames.reset();
    updateFrames.reset();
    drawFrames.reset();
    fallFrames.reset();
    flipFrames.reset();
    forceFrames.reset();
    swapFrames.reset();
}
tetris::Game::Game(sf::Vector2i gridSize, bool running)//Initializes grid and calls run.
{
    //Note: Will default grid size to 10x24 and auto run "run()" unless parameters passed to do different.

    this->gridSize = gridSize;//default tetris game board is 10*24
    grid.setup(sf::Vector2f(gridSize));//Initialize the size of the grid using the grid setSize method.
    if(running)
    {
        run();//Run the auto runner in the game class.
    }
}
tetris::Game::~Game()//Prints score to the console on close/gameOver.
{
    std::cout<<"Game Over: "<<grid.totalScore<<std::endl;
}
void tetris::Game::run()//This is the run method. Calling this window will create a playable game. Not thread-able: one window only.
{
    setup();//Basic setup for window and timers.

    //GameLoop
    while (window.isOpen())
    {
        if(totalFrames.check())
        {
            events();//Checks for keys pressed, force drop, and window closed;

            updates();//Updates game process.

            fall();//Force drop block if applicable.

            draw();//Draw all shapes held and from grid.
        }
        else
        {
            sf::sleep(sf::milliseconds(1000/240));//Sleep to save resources.
            //Sleeps for 41.667 milliseconds, which is 0.041 of a second.
        }
    }
}
void tetris::Game::swapBlock()
{
    static bool inUse = false;
    static sf::Color reserveColor;
    static unsigned int reserveState = 0, reserveType = 0;

    if(swapBool)
    {
        if(inUse)
        {
            //Backup color and state to temp:
            sf::Color tempColor = block.getFillColor();
            unsigned int tempState = currentBlockState,
                         tempType = currentBlockType;

            //Update current color and current state:
            block.setFillColor(reserveColor);
            currentBlockState = reserveState;
            currentBlockType = reserveType;

            //Backup reserve color and reserve state:
            reserveColor = tempColor;
            reserveState = tempState;
            reserveType = tempType;

            //setup the new current block.
            selectBlockVariations();
        }
        else
        {
            reserveColor = block.getFillColor();
            reserveState = currentBlockState;
            reserveType = currentBlockType;
            inUse = true;
            currentBlock.clear();
            createBlock();
        }
        //Reset block position on swapping.
        currentPosition = sf::Vector2<int>(myRandom.get(1,gridSize.x-5),0);
        resetTimers();
        swapBool = false;
    }
}
