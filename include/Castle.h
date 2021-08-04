#ifndef CASTLE_H
#define CASTLE_H

#include <iostream>
#include "Player.h"
#include "Room.h"

class Castle
{
   public:
      Castle();
      virtual ~Castle();
      const Room* getRoom(short l, short r, short c) const { return room[l][r][c]; }
      Room*& getRoom(short l, short r, short c) { return room[l][r][c]; }
      void printLevel(short l) const;
      void printLevel(const Player&) const;
      void printCastleContents() const;
      short findZot() const;
      void clearRoom(short l, short r, short c);

   private:
      Room* room[8][8][8];

      void createStairs();
      void createMonsters();
      void createItems();
      void createTreasures();
      void createCurses();
      Room*& getRandomUnassignedRoom(short level = -1);
      Room*& replaceRandomEmptyRoom(Room* ptr, short level = -1);
};

// random number: rand() % range + 1
short rnd(short range);


#endif // CASTLE_H
