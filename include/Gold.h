#ifndef GOLD_H
#define GOLD_H

#include "Room.h"

class Gold : public Room
{
public:
    Gold();
    std::string description() const;
};

#endif // GOLD_H
