#include "myinput.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
std::vector<int> mu::MyInput::keyboard()
{
    std::vector<int> keysPressed;
    for(auto i = 0; i < sf::Keyboard::KeyCount; ++i)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(i)))
        {
            keysPressed.push_back(i);
        }
    }
    return keysPressed;
}
std::vector<int> mu::MyInput::mouse()
{
    std::vector<int> mouseButtonsPressed;
    for(auto i = 0; i < sf::Mouse::ButtonCount; ++i)
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button(i)))
        {
            mouseButtonsPressed.push_back(i);
        }
    }
    return mouseButtonsPressed;
}
