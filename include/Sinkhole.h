#ifndef SINKHOLE_H
#define SINKHOLE_H

#include "Room.h"


class Sinkhole : public Room
{
public:
    Sinkhole();
    std::string description() const;
};

#endif // SINKHOLE_H
