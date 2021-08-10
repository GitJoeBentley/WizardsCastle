#ifndef COMMAND_H
#define COMMAND_H
#include "Player.h"
#include "Castle.h"
#include <string>

class Command
{
public:
    Command(Player& me, Castle& cast);
    virtual ~Command() = default;
    bool get();
    void help() const;
    char move(char type);  // returns content abbreviation of new location
    void reactToNewRoom(char roomtype);
    void south() const;
    void north() const;
    void east() const;
    void west() const;
    void up() const;
    void down() const;
    void flare() const;
    void gaze();
    void openChest();
    void setRoomExplored() const;
    bool quit();

    // These are helper, frequently-used accessor functions
    std::string race() const;
    int gp() const;
    std::string armor() const;

private:
    std::string command;
    Player& me;
    Castle& castle;
    char lastCommand = ' ';

    bool isValid() const;
    void randomMessage() const;
    Room*& currentRoom();
    Room* currentRoom() const;
    char rm() const;
    Location reactToNewRoom();
    void vendor();
    Location monster();
    void monsterTurn(Monster* mp, short webCount);
    void monsterDies(const std::string& name);
    void decrementWebCount(short& webcount);
    void map() const;
    void lamp() const;
    void clearRoom() const;
    void randomRecipe();

    // accessor functions to match original code
    short ST() const;
    short DX() const;
    short IQ() const;
};

#endif // COMMAND_H
