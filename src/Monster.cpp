#include "Monster.h"
using std::string;

const string Monster::Type[13] =
{"","Kobold","Orc","Wolf","Goblin","Ogre","Troll","Bear","Minotaur","Gargoyle","Chimera","Balrog","Dragon"};

Monster::Monster(short num)
    : Room('M'), number(num), hp(num+2)
{
}

std::string Monster::description() const
{
    return Type[number];
}

short Monster::getNumber() const
{
    return number;
}

short Monster::damage() const
{
    return 1 + short(number/2);
}

short Monster::getHP() const
{
    return hp;
}

void Monster::setHP(short amount)
{
    hp = amount;
}
