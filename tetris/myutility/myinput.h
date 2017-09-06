#ifndef MYINPUT_H
#define MYINPUT_H
#include <vector>
/*  Simple class that holds two static methods for acquiring vectors of booleans of button/keys pressed */
namespace mu
{
    class MyInput
    {
    public:
        static std::vector<int> keyboard();//Simple STATIC method to get a vector of booleans indicating which keys were pressed
        static std::vector<int> mouse();//Simple STATIC method to get a vector of booleans indicating which mouse buttons were pressed

        //Remember Static methods can be called without initializing the class:

        //Example:  std::vector<bool> keys = mu::MyInput::keyboard();
        //          returns a vector of booleans mapping to keys with values equal to [true/false].
        //          To test the maps, use example: if(keys[sf::Keyboard::Up]), will return true if up was pressed.
    };
}
#endif // MYINPUT_H
