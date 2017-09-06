#ifndef GRID_H
#define GRID_H
#include<SFML/Graphics.hpp>
#include<vector>
namespace tetris
{
    class Grid
    {
    protected:
        //Area is the grid's important contain data.
        std::vector<std::vector<sf::RectangleShape*> > area;

        //Area size is the size of the grid in (x,y) notation.
        sf::Vector2<float> areaSize;
    public:
        //Public members:
            //Block size: Affects the block sizes in this grid.
            //Total score: Is the total score this grid has calculated.
            //Score value: Is the score multiplier.
        unsigned int blockSize, totalScore, scoreValue;

        //Default constructor: takes grid size, block size, and score value. Will call setup().
        Grid(sf::Vector2<float> gridSize = {0,0}, unsigned int blockSize = 25, unsigned int scoreValue = 5);

        //Destruction, it will call free() to free heap data.
        ~Grid();

        //This method frees all heap data in this object.
        void free();

        //Reset total score method.
        void resetScore(unsigned int score = 0);

        //Basic setup for this object. Allows users to change grid size, block size, and score magnitude value.
        void setup(sf::Vector2<float> gridSize = {0,0}, unsigned int blockSize = 25, unsigned int scoreValue = 5);

        //Checks if block piece can fit in grid. returns fails if cannot.
        bool check(sf::Vector2<int> pos,std::vector<std::vector<sf::RectangleShape*> > newBlock);

        //Attempt to insert a configuration of blocks into the grid. Return false, if failed.
        bool insert(sf::Vector2<int> pos,std::vector<std::vector<sf::RectangleShape*> > newBlock);

        //Draw methods:
            //Draws stuff in the grid to the window.
            void draw(sf::RenderWindow &window);
            //Draws stuff relative to the grid to the window.
            void draw(sf::RenderWindow &window, std::vector<std::vector<sf::RectangleShape*> > outsiderBlock, sf::Vector2<int> pos);

        void cleanup();//We check if there is a tetris.
    };
}
#endif // GRID_H
