#include "Room.h"
using std::ostream;
using std::string;

Room::Room(char arg1, unsigned char arg2)
    : abbreviation(arg1), curse(arg2)
{}

Room::~Room()
{
    //dtor
}

ostream& operator<<(ostream& out, const Room& object)
{
    if (object.isExplored()) out << object.getAbbr();
    else out << '?';
    return out;
}

bool Room::isExplored() const
{
    return explored;
}

void Room::setExplored(bool tf)
{
    explored = tf;
}

unsigned char Room::getCurse() const
{
    return curse;
}

void Room::setCurse(unsigned char curs)
{
    curse = curs;
}
void Room::setRunestaff(bool runestaff)
{
    hasRunestaff = runestaff;
}

void Room::setOrbOfZot(bool orb)
{
    hasOrbOfZot = orb;
}

bool Room::hasTheRunestaff() const
{
    return hasRunestaff;
}

bool Room::hasTheOrbOfZot() const
{
    return hasOrbOfZot;
}

char Room::operator*() const
{
    return abbreviation;
}

char Room::getAbbr() const
{
    return abbreviation;
}

void Room::setRoomEmpty()
{
    abbreviation = '.';
    explored = true;
}

void Room::removeCurse()
{
    curse = 0;
}
