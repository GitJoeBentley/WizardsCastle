#ifndef CHEST_H
#define CHEST_H

#include "Room.h"


class Chest : public Room
{
public:
    Chest();
    std::string description() const
    {
        return "chest";
    }
};

#endif // CHEST_H
