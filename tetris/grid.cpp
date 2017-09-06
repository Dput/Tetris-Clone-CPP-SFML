#include "grid.h"

tetris::Grid::Grid(sf::Vector2<float> gridSize, unsigned int blockSize, unsigned int scoreValue)
{
    setup(gridSize,blockSize,scoreValue);//Setup our grid system.
    resetScore();//Reset score to 0.
}
tetris::Grid::~Grid()
{
    //Call the free method, which frees all of our heap data.
    free();
}
void tetris::Grid::free()
{
    //Free any memory in use by our grid system.

    //Double for_loop iterating our grid.
    for(auto i = 0; i < area.size(); ++i)
    {
        for(auto j = 0; j < area[i].size(); ++j)
        {
            if(area[i][j]!=0)//If we've found something free it and set it to 0;
            {
                delete area[i][j];
                area[i][j] = 0;
            }
        }
        area[i].clear();//Clear that row of data.
    }
    area.clear();//Clear all the data (row x column).

    //Grid will be unusable until a setup() has been established.
}
void tetris::Grid::resetScore(unsigned int score)
{
    //Resets the score to the provided value; defaults to 0.
    totalScore = score;
}
void tetris::Grid::setup(sf::Vector2<float> gridSize, unsigned int blockSize, unsigned int scoreValue)
{
    //Default methods used to create a new grid area to be used.
    free();//Free any data inside our grid if not empty.

    //Assign our grid a new size 2D( gridSize.x, gridSize.y );.
    area = std::vector<std::vector<sf::RectangleShape*> >(gridSize.y,std::vector<sf::RectangleShape*>(gridSize.x,0));

    //Assign our grids area size.
    areaSize = gridSize;

    //Assign our grids standard block size.
    this->blockSize = blockSize;

    //Assign our grid its default values for points made.
    this->scoreValue = scoreValue;
}
bool tetris::Grid::check(sf::Vector2<int> pos,std::vector<std::vector<sf::RectangleShape*> > newBlock)
{
    //Check if the block will fit / is valid.

    //Double loop to iterate the new configuration of blocks provided by newBlock.
    for(auto i = 0; i < newBlock.size(); ++i)
    {
        for(auto j = 0; j < newBlock[i].size(); ++j)
        {
            if(newBlock[i][j]!=0)//If we've found a applicable block piece.
            {
                //Validate if it's in our system spec: our grids size (x,y). Otherwise out of bounds.
                if(i+pos.y>=area.size() || j+pos.x>=area[0].size() || i+pos.y<0 || j+pos.x<0)
                {
                    return false;//Return false if out of bounds. AKA it isn't in our grid.
                }
                if(area[i+pos.y][j+pos.x]!=0)
                {
                    return false;//Return false if we have something already there, AKA it doesn't fit.
                }
            }
        }
    }
    return true;//If all tests passed, return true, we can take that block.
}
bool tetris::Grid::insert(sf::Vector2<int> pos,std::vector<std::vector<sf::RectangleShape*> > newBlock)
{
    //This method inserts the block into the grid

    //Double for_loop to iterate though the newBlock to be inserted.
    for(auto i = 0; i < newBlock.size(); ++i)
    {
        for(auto j = 0; j < newBlock[i].size(); ++j)
        {
            if(newBlock[i][j]!=0)//If we've found a block that is applicable; in our case the pointer not equal to 0.
            {
                if(area[i+pos.y][j+pos.x]!=0)//Check if there is something already there.
                {
                    return true;//Something there, return true. This usually triggers Game Over.
                }
                if(i+pos.y<area.size() || j+pos.x<area[0].size() || i+pos.y>=0 || j+pos.x>=0)//Out of bounds catch.
                {
                    //We do no take ownership of the block.
                    area[i+pos.y][j+pos.x] = new sf::RectangleShape;//We create a new block at the expected position.
                    area[i+pos.y][j+pos.x]->setFillColor(newBlock[i][j]->getFillColor());//We copy the color of the newBlock.
                    //Again we do not take ownership of the outside blocks. We've simply copy its color.
                    //Block positioning will be done at draw time, and based on where it is located in our grid system.
                }
            }
        }
    }
}
void tetris::Grid::draw(sf::RenderWindow &window)
{
    //Double for_loop iterating our grid. We will move each object in grid to it's rightful spot and draw them.
        //Moving them to their rightful spot in case their positions change. And also insert does not set position.
        //Print is in charge of positioning.
    for(auto i = 0; i < area.size(); ++i)
    {
        for(auto j = 0; j < area[i].size(); ++j)
        {
            if(area[i][j]!=0)
            {
                //Reset each blocks position. We've chose to enforce our systems block position on draw.
                area[i][j]->setPosition(blockSize*j,blockSize*i);
                //Reset each blocks size. We've chose to enforce our systems block sizes standards on draw.
                area[i][j]->setSize(sf::Vector2f(blockSize,blockSize));
                //Draw the applicable block to the window; to be displayed later.
                window.draw(*area[i][j]);
            }
            else
            {
                //TODO:
            }
        }
    }
}
void tetris::Grid::draw(sf::RenderWindow &window, std::vector<std::vector<sf::RectangleShape*> > outsiderBlock, sf::Vector2<int> pos)
{
    //This method draws a given set(s) of block using our grids coordinate system.

    //Double for_loop iterating through the outsiders block.
    for(auto i = 0; i < outsiderBlock.size(); ++i)
    {
        for(auto j = 0; j < outsiderBlock[i].size(); ++j)
        {
            if(outsiderBlock[i][j]!=0)//If we find a block piece that needs to be drawn, do the inner stuff.
            {
                //We'll set the block's position equal to adjustments outside of our grid (aka pos)
                    //And relative to it's position within it's own block formation.
                outsiderBlock[i][j]->setPosition(blockSize*(j+pos.x),blockSize*(i+pos.y));

                //We'll set each blocks size equal our standards. In our case it's [blockSize x blockSize].
                outsiderBlock[i][j]->setSize(sf::Vector2f(blockSize,blockSize));

                //And then we'll draw it to the windows; to be displayed later; now having our systems size and shape.
                window.draw(*outsiderBlock[i][j]);
            }
            else
            {
                //TODO:
            }
        }
    }
}
//Cleanup the game: determines tetris' and accumulate points. Also remove completed rows.
void tetris::Grid::cleanup()
{
    unsigned int tetrisRowCounter = 0,      //if this counter == a row size, we have a Tetris on that row.
                 tetrisHeightCounter = 0;   //counts height to be multiplied by scoreValue for total score earned (tetris).

    std::vector<unsigned int> removableRows;//Takes an integer of the removable rows index.

    for(auto i = 0; i < area.size(); ++i)//Circulate through the rows of this grid (y axis).
    {
        for(auto j = 0; j < area[i].size(); ++j)//Circulate through the column of this grid (x axis).
        {
            if(area[i][j]!=0)//If a particular block is not empty.
            {
                ++tetrisRowCounter;//Increment our row counter.
            }
            else
            {
                break;//Else break, because if one block is missing we can no longer get a tetris on that row.
                //This will break this->for_loop and check the next row.
            }
            if(tetrisRowCounter>=area[i].size())//If the whole row is filled.
            {
                removableRows.push_back(i);//We take note of the index of this row, to be deleted later.
                ++tetrisHeightCounter;//And we increase the tetris height counter to increase the rewards for this tetris.
                totalScore += scoreValue*tetrisHeightCounter;//We add the scores to the total score.
            }
        }
        tetrisRowCounter=0;//Reset tetris row counter every row.
    }
    //Eventually we'll have to remove the tetris'ed rows, here we are.
    for(auto i = 0; i < removableRows.size(); ++i)//First for_loop finds us which row to remove.
    {
        for(auto j = 0; j < area[removableRows[i]].size(); ++j)//Second for_loop deletes the heap data in that row.
        {
            delete area[removableRows[i]][j];//Delete heap data.
            area[removableRows[i]][j] = 0;//Set pointer of deleted data to 0; in case accidents.
        }
        area[removableRows[i]].clear();//Clear that row. Its size becomes 0.
        area.erase(area.begin()+removableRows[i]);//Erase that row; remove it from the vector.
        area.insert(area.begin(),std::vector<sf::RectangleShape*>(areaSize.x,0));//Insert a new row to the top of the grid.
        //SINCE WE FILLED A NEW ROW TO THE TOP OF THE GRID, OUR ROW COUNTS IS STILL THE SAME.
            //BECAUSE OF THAT WE CAN CONTINUE DELETING "LOWER" ROWS AS USUAL.
        //Our delete process will delete from LOW rows to HIGH rows. 0->rowSize.y;
        //Example: We have a grid of 10x10, at row 5,7,9 we have tetris'. Our system deletes row 5 first.
            //Now we have a 10x9 array and the rest of the numbers will be off. But we insert a new row to the very top.
            //Now we have a 10x10 row again. Everything from rows 1-4 moved up an index value to 2-5.
            //And we'll be able to continue onwards to free rows 7 and 9.
            //For every row we free, we'll again, move all of the above rows down a notch and insert a new row up top.
    }
}
