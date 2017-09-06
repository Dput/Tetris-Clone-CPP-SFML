#ifndef MYTIME_H
#define MYTIME_H
#include<SFML/System/Clock.hpp>
namespace mu
{
    class MyTime
    {
    private:
        sf::Clock clock;
        float limit, flimit, current, previous;
    public:
        MyTime(float _limit = 1);
        bool check(bool catchup = true);
        void set(float _limit);
        void reset(float _limit = -1, float _current = 0, float _previous = 0);
        void setClock(sf::Clock _clock);
    };
}
#endif // MYTIME_H
