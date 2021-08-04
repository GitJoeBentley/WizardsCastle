#include "Pool.h"

Pool::Pool() : Room('P')
{
}

std::string Pool::description() const
{
    return "magic pool";
}
