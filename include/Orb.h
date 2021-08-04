#ifndef ORB_H
#define ORB_H

#include "Room.h"


class Orb : public Room
{
public:
    Orb();
    std::string description() const;
};

#endif // ORB_H
