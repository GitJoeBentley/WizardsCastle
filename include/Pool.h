#ifndef POOL_H
#define POOL_H

#include "Room.h"


class Pool : public Room
{
public:
    Pool();
    std::string description() const;
};

#endif // POOL_H
