#ifndef MONSTER_H
#define MONSTER_H
#include <string>
#include "Room.h"


class Monster : public Room
{
public:
    explicit Monster(short num);
    static const std::string Type[13];

    std::string description() const;
    short getNumber() const;
    short damage() const;
    short getHP() const;
    void setHP(short amount);

private:
    short number;  // Monster number determines HP (hit points) and Damage
    short hp;
};

#endif // MONSTER_H
