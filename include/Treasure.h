#ifndef TREASURE_H
#define TREASURE_H

#include "Room.h"
#include <string>


class Treasure : public Room
{
public:
    Treasure(short num);
     static const std::string Type[9];
    std::string description() const;
    short getNumber() const;

private:
    short number;  // Treasure number determines its value when selling
    short value() const;
};

#endif // TREASURE_H
