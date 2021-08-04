#ifndef ROOM_H
#define ROOM_H
#include <iostream>
#include <string>

class Room
{
public:
    Room(std::string arg1, char arg2, int curs = 0);
    Room(char arg2, int curs = 0);
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
    bool explored = false; // = false;  // change this to false
    unsigned char curse = 0;             // curse = 0 means no curse
    bool hasRunestaff = false;
    bool hasOrbOfZot = false;
};

std::ostream& operator<<(std::ostream& out, const Room& object);

#endif // ROOM_H
