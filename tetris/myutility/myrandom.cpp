#include "myrandom.h"

mu::MyRandom::MyRandom(unsigned int _seed)
{
    seed = _seed;
    random.seed(seed);
}
