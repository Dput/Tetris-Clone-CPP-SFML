#include "mytime.h"

mu::MyTime::MyTime(float _limit)
{
    set(_limit);
    current = previous = 0;
}
bool mu::MyTime::check(bool catchup)
{
    flimit = 1000/limit;
    current = clock.getElapsedTime().asMilliseconds();
    if(flimit<(current - previous)){
        if(catchup){
            while((previous + flimit) < current)
                previous += flimit;
        }else{
            previous += flimit;
        }
        return true;
    }else{
        if(catchup && ((previous + flimit) < current)){
            while((previous + flimit) < current)
                previous += flimit;
        }
    }
    return false;
}
void mu::MyTime::set(float _limit){
    if(_limit > 0)
        limit = _limit;
    else
        limit = 1;
}
void mu::MyTime::reset(float _limit, float _current, float _previous){
    if(_limit > 0)
        limit = _limit;
    current = _current;
    previous = _previous;
    clock.restart();
}
void mu::MyTime::setClock(sf::Clock _clock){
    clock = _clock;
}
