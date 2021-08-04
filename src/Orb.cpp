#include "Orb.h"

Orb::Orb() : Room('O')
{
}

std::string Orb::description() const
{
    return "a crystal orb";
}
