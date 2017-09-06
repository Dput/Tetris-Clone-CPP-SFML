#ifndef MYRANDOM_H
#define MYRANDOM_H
#include <random>
#include <ctime>
/*  Simple class that generates random unsigned integers and doubles */
namespace mu
{
    class MyRandom
    {
    public:
        unsigned int seed;
        std::mt19937 random;
        MyRandom(unsigned int _seed = (time(0)*getpid()));

        template<class T>
        T get(T min = 0, T max = 0)
        {
            return 0;
        }
    };
    template<>
    inline int MyRandom::get(int min, int max)
    {
        std::uniform_int_distribution<int> uniform(min,max);
        return uniform(random);
    }
    template<>
    inline unsigned int MyRandom::get(unsigned int min,unsigned  int max)
    {
        std::uniform_int_distribution<int> uniform(min,max);
        return uniform(random);
    }
    template<>
    inline double MyRandom::get(double min, double max)
    {
        std::uniform_real_distribution<double> uniform(min,max);
        return uniform(random);
    }
}
#endif // MYRANDOM_H
