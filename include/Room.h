#ifndef ROOM_H
#define ROOM_H
#include <iostream>
#include <string>

class Room
{
public:
    Room(char arg2, unsigned char curs = 0);
    virtual ~Room();

    bool isExplored() const;
    void setExplored(bool tf = true);

    unsigned char getCurse() const;
    void setCurse(unsigned char curs);
    void removeCurse();

    void setRunestaff(bool runestaff);
    bool hasTheRunestaff() const;

    void setOrbOfZot(bool orb);
    bool hasTheOrbOfZot() const;

    char operator*() const;
    char getAbbr() const;
    void setRoomEmpty();

    virtual std::string description() const = 0;

private:
    char abbreviation;
    bool explored = false; // = true;  // change this to true for debugging
    unsigned char curse = 0;             // curse = 0 means no curse
    bool hasRunestaff = false;
    bool hasOrbOfZot = false;
};

std::ostream& operator<<(std::ostream& out, const Room& object);

#endif // ROOM_H
