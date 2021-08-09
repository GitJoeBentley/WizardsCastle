#include <fstream>
#include "Castle.h"
#include "Entrance.h"
#include "Empty.h"
#include "StairsDown.h"
#include "StairsUp.h"
#include "Monster.h"
#include "Pool.h"
#include "Chest.h"
#include "Gold.h"
#include "Flare.h"
#include "Warp.h"
#include "Sinkhole.h"
#include "Orb.h"
#include "Book.h"
#include "Vendor.h"
#include "Treasure.h"
#include "Curse.h"
using namespace std;

// om number: rand() % range + 1
short rnd(short range)
{
    return rand() % range + 1;
}


Castle::Castle()
{
    // Start off empty rooms using a null poshorter
    for (short l = 0; l < 8; l++)
        for (short r = 0; r < 8; r++)
            for (short c = 0; c < 8; c++)
                room[l][r][c] = nullptr;

    room [0][0][3] = new Entrance;
    createStairs();
    createMonsters();
    createItems();
    createTreasures();
    createCurses();

    Room* roomPtr;

    // assign runestaff
    //roomPtr = room[0][1][2] = new Monster(1);            // ***** this is for debugging
    roomPtr = getRandomUnassignedRoom() = new Monster(rnd(12));
    roomPtr->setRunestaff(true);

    // create warp with Orb Of Zot
    // roomPtr = room[1][2][3] = new Warp;            // ***** this is for debugging
    roomPtr = getRandomUnassignedRoom() = new Warp;
    roomPtr->setOrbOfZot(true);

    // Set unassigned rooms to empty
    for (short l = 0; l < 8; l++)
        for (short r = 0; r < 8; r++)
            for (short c = 0; c < 8; c++)
                if (!room[l][r][c]) room[l][r][c] = new Empty;
}

Castle::~Castle()
{
    for (short l = 0; l < 8; l++)
        for (short r = 0; r < 8; r++)
            for (short c = 0; c < 8; c++)
                delete room[l][r][c];
}

Room*& Castle::getRandomUnassignedRoom(short level)
{
    short count = 0, l, r, c;
    while (count < 1)
    {
        l = (level == -1) ? rand() % 8 : level;
        r = rand() % 8;
        c = rand() % 8;
        if (!room[l][r][c]) return room[l][r][c];
    }
    return room[0][0][0];  // this should never happen
}

Room*& Castle::replaceRandomEmptyRoom(Room* roomPtr, short level)
{
    short count = 0, l, r, c;
    while (count < 1)
    {
        l = (level == -1) ? rand() % 8 : level;
        r = rand() % 8;
        c = rand() % 8;
        if (**room[l][r][c]=='.')
        {
            delete room[l][r][c];
            room[l][r][c] = roomPtr;
            ++count;
        }
    }
    return room[l][r][c];
}

void Castle::printLevel(short l) const
{
    for (short r = 0; r < 8; ++r)
    {
        for ( short c = 0; c < 8; ++c)
        {
            cout << ' ' << **getRoom(l,r,c) << ' ';
        }
        cout << std::endl;
    }
    cout << std::endl;
}

void Castle::printLevel(const Player& me) const
{
    short myL = me.getLevel();
    short myR = me.getRow();
    short myC = me.getColumn();
    cout << endl;
    for (short r = 0; r < 8; ++r)
    {
        for ( short c = 0; c < 8; ++c)
        {
            if (r == myR && c == myC) cout << '<';
            else cout << ' ';
            cout << *getRoom(myL,r,c);
            if (r == myR && c == myC) cout << '>';
            else cout << ' ';
            cout << "  ";
        }
        cout << endl << endl;
    }
    me.printLocation();
}

// create stairs going up and down
void Castle::createStairs()
{
    short r,c, count;
    for (short l = 0; l < 7; ++l)
    {
        count = 0;
        while (count < 2)
        {
            r = rand() % 8;
            c = rand() % 8;
            if (!getRoom(l,r,c))
            {
                room[l][r][c] = new StairsDown;
                room[l+1][r][c] = new StairsUp;
                count++;
            }
        }
    }
}

void Castle::createMonsters()
{
    for (short level = 0; level < 8; ++level)
    {
        for (auto monsterType = 1; monsterType <= 12; monsterType++)
        {
            getRandomUnassignedRoom(level) = new Monster(monsterType);
        }
    }
}

// Create 3 each per level of Pool, Chest, Gold Pieces, Flares, Warps, Sinkholes, Crystal Orbs, Books
void Castle::createItems()
{
    for (short level = 0; level < 8; ++level)
    {
        for (short num = 0; num < 3; ++num) getRandomUnassignedRoom(level) = new Pool;
        for (short num = 0; num < 3; ++num) getRandomUnassignedRoom(level) = new Chest;
        for (short num = 0; num < 3; ++num) getRandomUnassignedRoom(level) = new Gold;
        for (short num = 0; num < 3; ++num) getRandomUnassignedRoom(level) = new Flare;
        for (short num = 0; num < 3; ++num) getRandomUnassignedRoom(level) = new Warp;
        for (short num = 0; num < 3; ++num) getRandomUnassignedRoom(level) = new Sinkhole;
        for (short num = 0; num < 3; ++num) getRandomUnassignedRoom(level) = new Orb;
        for (short num = 0; num < 3; ++num) getRandomUnassignedRoom(level) = new Book;
        for (short num = 0; num < 3; ++num) getRandomUnassignedRoom(level) = new Vendor;
    }
    // For debugging
    //getRoom(0,0,0) = new Sinkhole;
    //getRoom(0,1,1) = new Sinkhole;
    //getRoom(1,0,0) = new Flare;
    //getRoom(1,1,1) = new Gold;
}

void Castle::createTreasures()
{
    for (short tr = 1; tr <= 8; ++tr)
    {
        getRandomUnassignedRoom() = new Treasure(tr);
    }
}

void Castle::createCurses()
{
    // debugging
    //getRoom(0,0,0) = new Empty(1);
    //getRoom(0,1,1) = new Empty(2);
    //getRoom(0,2,2) = new Empty(3);
    for (short curs = 0; curs < 4; ++curs)
    {
        getRandomUnassignedRoom()= new Empty(curs);
    }
}

void Castle::printCastleContents() const
{
    ofstream fout("castlecontents.txt");
    for (short l = 0; l < 8; ++l)
    {
        fout << "Level " << l << endl;
        for (short r = 0; r < 8; ++r)
        {
            for ( short c = 0; c < 8; ++c)
            {
                fout << ' ' << **getRoom(l,r,c) << ' ';
            }
            fout << std::endl;
        }
        fout << std::endl;
    }
    char id;
    for (short l = 0; l < 8; ++l)
    {
        for (short r = 0; r < 8; ++r)
        {
            for ( short c = 0; c < 8; ++c)
            {
                id = room[l][r][c]->getAbbr();
                fout << "(" << l << ',' << r <<',' << c << ") "
                     << id << ' '
                     << room[l][r][c]->description() << ' ';
                if (id == '.' and room[l][r][c]->getCurse())
                {
                    fout << Curse::name[room[l][r][c]->getCurse()] << ' ';
                }
                if (id == 'M')
                {
                    if (room[l][r][c]->hasTheRunestaff())
                        fout << "has Runestaff ";
                }
                if (id == 'W')
                {
                    if (room[l][r][c]->hasTheOrbOfZot())
                        fout << "has the Orb of Zot ";
                }

                fout << endl;
            }
            fout << std::endl;
        }
        fout << std::endl;
    }
    fout.close();
    //  system("notepad castlecontents.txt");
}

short Castle::findZot() const
{
    for (short l = 0; l < 8; ++l)
    {
        for (short r = 0; r < 8; ++r)
        {
            for ( short c = 0; c < 8; ++c)
            {
                if (room[l][r][c]->hasTheOrbOfZot()) return 100*l+10*r+c;
            }
        }
    }
    return 0;
}

void Castle::clearRoom(short l, short r, short c)
{
    delete room[l][r][c];
    room[l][r][c] = new Empty;
}


