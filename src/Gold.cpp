#include "Gold.h"

Gold::Gold() : Room('G')
{
    //ctor
}

std::string Gold::description() const
{
    return "gold pieces";
}
