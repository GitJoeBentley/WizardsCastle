#ifndef EMPTY_H
#define EMPTY_H

#include <Room.h>


class Empty : public Room
{
public:
    Empty(unsigned char curs = 0);
    virtual ~Empty();
    std::string description() const
    {
        return "an empty room";
    }

private:
};

#endif // EMPTY_H
