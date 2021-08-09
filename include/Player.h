#ifndef PLAYER_H
#define PLAYER_H
//#include "Castle.h"
#include "Room.h"
#include "Location.h"
#include "Monster.h"
#include <string>
#include <bitset>  // for treasures, curses
#include <algorithm>
#include <utility>

class Castle;

class Player
{
public:
    Player(Castle& cast);
    virtual ~Player() = default;
    static const std:: string Race[5];
    static const std::string Armor[4];
    static const std::string Weapon[4];
    static const Location ExitCastle;

    void changeSex();
    void changeRace();
    std::string getRace() const;

    bool isBlind() const;
    void setBlind();
    void cureBlindness();

    void setDexterity(unsigned char value);
    void setStrength(unsigned char value);
    void setIntelligence(unsigned char value);

    void printLocation() const;
    void printAttributes() const;
    Location getLocation() const;
    unsigned short getLevel() const;
    unsigned short getRow() const;
    unsigned short getColumn() const;
    void goDown();
    void goUp();
    std::string getWeaponAsString() const;
    char getSex() const;

    std::string getArmorAsString() const;
    short getArmor_durability() const { return armor_durability; }
    Room* currentRoom() const;
    Room*& currentRoom();

    void setRow(unsigned short);
    void setColumn(unsigned short);
    void setLevel(unsigned short);
    void setArmor(short type);
    void setWeapon(int type);
    short getStrength() const;
    short getDexterity() const;
    short getIntelligence() const;
    short* ptrStrength();
    short* ptrDexterity();
    short* ptrIntelligence();
    void incrementStrength(short amount);
    void incrementDexterity(short amount);
    void incrementIntelligence(short amount);
    void decrementStrength(short amount);
    void decrementDexterity(short amount);
    void decrementIntelligence(short amount);
    bool getHasOrbOfZot() const;
    bool hasLamp() const;
    short getFlares() const;
    int getGold() const;
    void setGold(int amount);
    short addFlares(short howmany);
    int addGold(int howmany);
    void stickBookToHands();
    void dissolveBookStuckToHands() { bookStuckToHands = false; }
    void damage(short x);
    void setTreasure(int num);
    size_t countTreasures() const;
    std::bitset<9> getTreasures() const;
    void sellTreasure(size_t pos, int price);
    bool hasTreasure(size_t num);
    void buyArmor();   // from vendor
    void buyWeapon();  // from vendor
    void buyPotion(const std::string& type);
    void buyLamp();
    std::pair<bool,char> attack();  // return bool = alive/dead, char = direction of retreat (0 = no retreat)
    std::pair<bool,char> attackVendor();
    void attackMonster();
    void openBook();
    bool openChest();
    Location move(char type);
    void drink();
    bool isLethargic() const;
    bool isBookStuckToHands() const;
    short getWeapon() const;
    short getArmor() const { return armor; }
    void setLamp();
    short getRandomTreasure() const;
    void addCurse(size_t pos);
    void removeCurse(size_t pos);
    bool hasCurse(size_t pos);
    void clearRoom() const;
    void setRunestaff();
    bool hasRunestaff() const;
    void setOrbOfZot();
    void cheat();
    short getTurns() const;
    void incrementTurns();

private:
    Castle& castle;
    Location location;
    unsigned char race;
    char sex;
    short strength;
    short dexterity;
    short intelligence = 8;
    int gold = 60;
    short flares = 0;
    short turns = 0;
    short armor;
    short armor_durability;
    short weapon;
    std::bitset<9> treasures;
    std::bitset<4> curses;
    bool lamp = false;
    bool blind = false;
    bool bookStuckToHands = false;
    bool runestaff = false;
    bool hasOrbOfZot = false;
    bool vendorsAreAngry = false;
    bool lethargic = false;

    void getPotion(short* attributePtr);
    void vendorTurn();
    char roomType() const;
    void exit();
};

char yourchoice(const std::string& prompt, const std::string& allowable, const std::string& errormsg);
int yourchoice(const std::string& prompt, int max);

#endif // PLAYER_H
