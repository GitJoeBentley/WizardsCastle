#include "Treasure.h"
using std::string;

const string Treasure::Type[9] =
{"","Ruby Red","Norn Stone","Pale Pearl","Opal Eye","Green Gem","Blue Flame","Palintir","Silmaril"};

Treasure::Treasure(short num) : Room('T'), number(num)
{
}

short Treasure::getNumber() const
{
    return number;
}

std::string Treasure::description() const
{
    return Type[number];
}

short Treasure::value() const
{
    return number * 1500;
}
