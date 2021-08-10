#include "Player.h"
#include "Castle.h"
#include "Monster.h"
#include "Vendor.h"
#include "Empty.h"
#include "Treasure.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <cctype>
#include <cstring>
using namespace std;

const string Player::Race[5] = {"","Hobbit","Elf","Human","Dwarf"};
const string Player::Armor[4] = {"Nothing","Leather","Chainmail","Plate"};
const string Player::Weapon[4] = {"Nothing","Dagger","Mace","Sword"};
const Location Player::ExitCastle(8,8,8);

Player::Player(Castle& cast) : castle(cast)
{
    char choice;
    short nchoice;
    int additional_points = 8;
    // int additional_points = 30;
    cout << "All right, bold one.\a" << endl;
    choice = yourchoice("You may be an elf, dwarf, man, or hobbit.\n\nYour choice? ","EDMH","** That was incorrect. Please type E, D, M, OR H.");
    race = static_cast<unsigned char>(string(" HEMD").find(choice));
    strength = 2 + race * 2;
    dexterity = 14 - race * 2;
    intelligence = 8;
    //dexterity = intelligence = 18;  // debug oliver
    if (race == 1) additional_points = 4;
    choice = yourchoice("Which sex do you prefer? ","MF",string("** Cute ")+Race[race]+", real cute.  Try M or F.");
    cout << "Ok, " << Race[race]  << ", you have the following attributes :" << endl;
    cout << "Strength = " << static_cast<int>(strength)
         << "  Intelligence = " << static_cast<int>(intelligence)
         << "  Dexterity = " << static_cast<int>(dexterity) << endl;
    cout << "and " << additional_points << " points to allocate as you wish." << endl << endl;
    nchoice = yourchoice("How many points do you wish to add to your strength? ",additional_points);
    additional_points -= nchoice;
    strength += nchoice;
    if (additional_points > 0)
    {
        nchoice = yourchoice("How many points do you wish to add to your intelligence? ",additional_points);
        additional_points -= nchoice;
        intelligence += nchoice;
    }
    if (additional_points > 0)
    {
        nchoice = yourchoice("How many points do you wish to add to your dexterity? ",additional_points);
        additional_points -= nchoice;
        dexterity += nchoice;
    }
    cout << "Ok, " << Race[race] << ", you have " << gold << " gold pieces (GP's)." << endl;
    choice = yourchoice("\nThese are the types of armor you can buy :\nPlate<30> Chainmail<20> Leather<10> Nothing<0>\n\nYour choice? ","PCLN",\
                        string("** Are you a ")+ Race[race] + " or a " + Monster::Type[rand()%12+1] + "?");
    armor = static_cast<short>(string("NLCP").find(choice));
    armor_durability = armor * 7;
    gold -= armor * 10;
    cout << "Ok, bold " << Race[race] << ", you have " << gold << " GP's left." << endl;
    choice = yourchoice("\nThese are the types of weapons you can buy :\nSword<30> Mace<20> Dagger<10> Nothing<0>\n\nYour choice? ","SMDN",\
                        "** Is your IQ really 8 ?");
    weapon = static_cast<short>(string("NDMS").find(choice));
    gold -= weapon * 10;
    if (gold >= 20)
    {
        choice = yourchoice("Do you want to buy a lamp for 20 GP's? ","YN","** Please answer YES or NO");
        if (choice == 'Y')
        {
            lamp = true;
            gold -= 20;
        }
    }
    if (gold > 0)
    {
        cout << "Ok, " + Race[race] + ", you have " + to_string(gold) + " gold pieces left.\n\n";
        nchoice = yourchoice("Flares cost 1 GP each.  How many do you want? ",gold);
        gold -= nchoice;
        flares = nchoice;
    }
    currentRoom()->setExplored(true);
}

void Player::clearRoom() const
{
    castle.clearRoom(getLevel(),getRow(),getColumn());
    currentRoom()->setExplored();
}

void Player::printLocation() const
{
    //cout << "\nYou are at ( " << location / 10 % 10 + 1 << " , " << location % 10 + 1 << " ) Level " << location / 100 + 1 << " .\n\n";
    cout << "\nYou are at " << location << " .\n\n";
}

void Player::printAttributes() const
{
    cout << "Strength = " << static_cast<int>(strength)
         << "  Intelligence = " << static_cast<int>(intelligence)
         << "  Dexterity = " << static_cast<int>(dexterity) << endl;
    cout << "Treasures = " << treasures.count() << "  Flares = " << flares << "  Gold Pieces = " << gold << endl;
    cout << "Weapon = " << Weapon[weapon] << "  Armor = " << Armor[armor];
    if (hasLamp()) cout << "  and a lamp";
    cout << endl << endl;
}

void Player::changeSex()
{
    sex = sex == 'M' ? 'F' : 'M';
}

std::string Player::getRace() const
{
    return Race[race];
}

Location Player::getLocation() const
{
    return location;
}

unsigned short Player::getLevel() const
{
    return location.level();
}

unsigned short Player::getRow() const
{
    return location.row();
}

unsigned short Player::getColumn() const
{
    return location.column();
}

std::string Player::getWeaponAsString() const
{
    return Weapon[weapon];
}

char Player::getSex() const
{
    return sex;
}

std::string Player::getArmorAsString() const
{
    return Armor[armor];
}

void Player::changeRace()
{
    bool gotNewRace = false;
    unsigned char newRace;
    while (!gotNewRace)
    {
        newRace = static_cast<unsigned char>(rnd(4));
        if(race != newRace)
        {
            race = newRace;
            gotNewRace = true;
        }
    }
}

bool Player::isBlind() const
{
    return blind;
}

void Player::setBlind()
{
    blind = true;
}

void Player::cureBlindness()
{
    blind = false;
}

void Player::setDexterity(unsigned char value)
{
    dexterity = value;
}

void Player::setStrength(unsigned char value)
{
    strength = value;
}

void Player::setIntelligence(unsigned char value)
{
    intelligence = value;
}

void Player::setTreasure(int num)
{
    treasures.set(num);
}

Room* Player::currentRoom() const
{
    return castle.getRoom(getLevel(),getRow(),getColumn());
}

Room*& Player::currentRoom()
{
    return castle.getRoom(getLevel(),getRow(),getColumn());
}

void Player::setRow(unsigned short row)
{
    location.row() = row;
}

void Player::setColumn(unsigned short col)
{
    location.column() = col;
}

void Player::setLevel(unsigned short lev)
{
    location.level() = lev;
}

void Player::goDown()
{
    location.incLevel();
}

void Player::goUp()
{
    location.decLevel();
}

void Player::setArmor(short type)
{
    armor = type;
    armor_durability = type * 7;
}

void Player::setWeapon(short type)
{
    weapon = type;
}

short Player::getStrength() const
{
    return strength;
}
void Player::buyArmor()
{
    char choice;
    bool incomplete = true;
    cout << "\nOk, " << getRace() << ", you have " << gold << " GP's and " << Armor[armor] << " armor.\n\n";
    while (incomplete)
    {
        string prompt = "These are the types of armor you can buy :\nNothing<0> Leather<1250> ";
        string selection = "NLCP";
        if (gold >= 1500)
        {
            prompt += "Chainmail<1500> ";
        }
        if (gold >= 2000)
        {
            prompt += "Plate<2000>";
        }
        cout << prompt << endl;

        choice = yourchoice("\nYour choice? ",selection,"** Don't be silly.  Choose a selection");
        if (choice == 'N') incomplete = false;
        else if (choice == 'L')
        {
            armor = 1;
            armor_durability = 7;
            gold -= 1250;
            incomplete = false;
        }
        else if (choice == 'C')
        {
            if (gold > 1500)
            {
                armor = 2;
                armor_durability = 14;
                gold -= 1500;
                incomplete = false;
            }
            else
            {
                cout << "\n** You can afford Chainmail armor!\n\n";
            }
        }
        if (choice == 'P')
        {
            if (gold > 2000)
            {
                armor = 3;
                armor_durability = 21;
                gold -= 2000;
                incomplete = false;
            }
            else
            {
                cout << "**  You can afford Plate armor!\n\n";
            }
        }
    }
    cout << endl;
}

void Player::buyWeapon()
{
    char choice;
    bool incomplete = true;
    cout << "\nYou have " << gold << " GP's left with " << Weapon[weapon] << " in hand.\n\n";
    while (incomplete)
    {
        string prompt = "These are the types of weapons you can buy :\nNothing<0> Dagger<1250> ";
        string selection = "NDMS";
        if (gold >= 1500)
        {
            prompt += "Mace<1500> ";
        }
        if (gold >= 2000)
        {
            prompt += "Sword<2000>";
        }
        cout << prompt << endl;

        choice = yourchoice("\nYour choice? ",selection,"** Try choosing a selection!");
        if (choice == 'N') incomplete = false;
        else if (choice == 'D')
        {
            weapon = 1;
            gold -= 1250;
            incomplete = false;
        }
        else if (choice == 'M')
        {
            if (gold > 1500)
            {
                weapon = 2;
                gold -= 1500;
                incomplete = false;
            }
            else
            {
                cout << "\n** Your Dungeon Express card - you left home without it!\n\n";
            }
        }
        if (choice == 'S')
        {
            if (gold > 2000)
            {
                weapon = 3;
                gold -= 2000;
                incomplete = false;
            }
            else
            {
                cout << "\n** Your Dungeon Express card - you left home without it!\n\n";
            }
        }
    }
    cout << endl;
}

void Player::buyPotion(const string& type)
{
    short* attributePtr;

    if (type == "Strength") attributePtr = &strength;
    else if (type == "Dexterity") attributePtr = &dexterity;
    else attributePtr = &intelligence;
    unsigned short amount = 0;

    string prompt = "Do you want to buy a potion of " + type + " for 1000 GP's? ";
    char choice;
    while (gold >= 1000)
    {
        choice = yourchoice(prompt,"YN","** Please answer YES or NO");
        if (choice == 'Y')
        {
            getPotion(attributePtr);
            gold -= 1000;
            cout << "Your " << type << " is now ";
            if (type == "Strength") amount = strength;
            if (type == "Dexterity") amount = dexterity;
            if (type == "Intelligence") amount = intelligence;
            cout << amount << ".\n\n";
        }
        else break;
    }
}

short Player::getDexterity() const
{
    return dexterity;
}
short Player::getIntelligence() const
{
    return intelligence;
}

short* Player::ptrStrength()
{
    return &strength;
}

short* Player::ptrDexterity()
{
    return &dexterity;
}

short* Player::ptrIntelligence()
{
    return &intelligence;
}

void Player::incrementStrength(short amount)
{
    strength = strength + amount > 18 ? 18 : strength + amount;
}

void Player::incrementDexterity(short amount)
{
    dexterity = dexterity + amount > 18 ? 18 : dexterity + amount;
}

void Player::incrementIntelligence(short amount)
{
    intelligence = intelligence + amount > 18 ? 18 : intelligence + amount;
}

void Player::decrementStrength(short amount)
{
    strength = strength - amount < 0 ? 0 : strength - amount;
}

void Player::decrementDexterity(short amount)
{
    dexterity = dexterity - amount < 0 ? 0 : dexterity - amount;
}

void Player::decrementIntelligence(short amount)
{
    intelligence = intelligence - amount < 0 ? 0 : intelligence - amount;
}

bool Player::getHasOrbOfZot() const
{
    return hasOrbOfZot;
}

bool Player::hasLamp() const
{
    return lamp;
}

size_t Player::countTreasures() const
{
    return treasures.count();
}

std::bitset<9> Player::getTreasures() const
{
    return treasures;
}

void Player::sellTreasure(size_t pos, int price)
{
    treasures.set(pos,false);
    gold += price;
}

bool Player::hasTreasure(size_t num)
{
    return treasures.test(num);
}

bool Player::isLethargic() const
{
    return lethargic;
}

bool Player::isBookStuckToHands() const
{
    return bookStuckToHands;
}

short Player::getWeapon() const
{
    return weapon;
}

short Player::getFlares() const
{
    return flares;
}
int Player::getGold() const
{
    return gold;
}

void Player::setGold(int amount)
{
    gold = amount;
}

short Player::addFlares(short howmany)
{
    return flares += howmany;
}

int Player::addGold(int howmany)
{
    return gold += howmany;
}

void Player::setLamp()
{
    lamp = true;
}

void Player::addCurse(size_t pos)
{
    curses.set(pos,true);
}

void Player::removeCurse(size_t pos)
{
    curses.set(pos,false);
}

bool Player::hasCurse(size_t pos)
{
    return curses.test(pos);
}

void Player::setRunestaff()
{
    runestaff = true;
}

bool Player::hasRunestaff() const
{
    return runestaff;
}

void Player::setOrbOfZot()
{
    hasOrbOfZot = true;
}

short Player::getTurns() const
{
    return turns;
}

void Player::incrementTurns()
{
    turns++;
    if (hasCurse(1)) turns++;
}

char Player::roomType() const
{
    return currentRoom()->getAbbr();
}

void Player::stickBookToHands()
{
    bookStuckToHands = true;
}

void Player::damage(short x)
{
    strength -= static_cast<short>(x - std::max(x - armor,0));
    armor_durability -= std::min(x,armor);
}

void Player::getPotion(short* attributePtr)
{
    short potion;
    potion = rnd(6);
    if (potion + *attributePtr > 18) potion = 18 - *attributePtr;
    *attributePtr += potion;
}

void Player::buyLamp()
{
    string prompt = "\nDo you want to buy a lamp for 1000 GP's? ";
    char choice;
    choice = yourchoice(prompt,"YN","** Please answer YES or NO");
    if (choice == 'Y')
    {
        lamp = true;
        gold -= 1000;
        cout << "\nIt's guaranteed to outlive you!\n\n";
    }
}

std::pair<bool,char>  Player::attackVendor()
{
    char choice = 0;
    bool attackContinues = true;
    bool playerGetFirstAttack = !(lethargic or blind or (dexterity < rnd(9)+rnd(9)) or weapon == 0 or bookStuckToHands);
    bool firstTimeThruLoop = true;
    bool playerHits;
    int r;
    string prompt;
    string enemy = currentRoom()->description();
    if (enemy == "a vendor") enemy = "vendor";

    int vendorHP = 15;
    cout << "\nYou'll be sorry you did that!\n";

    while (attackContinues)
    {
        if ((playerGetFirstAttack && firstTimeThruLoop) or !firstTimeThruLoop)
        {
            prompt = string("\nYou're facing a " + enemy + "!\n\n")
                     + "You may attack or retreat.\n";
            if (rand()%3 > 0) prompt += "You can also attempt a bribe.\n\n";
            prompt += string("Your strength is " + to_string(strength))
                      + " and your dexterity is " + to_string(dexterity) + " .\n\nYour choice? ";
            choice = yourchoice(prompt,"ABR","** Choose one of the options listed.\n");
            if (choice == 'A')
            {
                if (!weapon or !bookStuckToHands)  // If no weapon, turn is forfeited
                {
                    r = rand() % 20 + 1;
                    if ((blind and dexterity >= r + 3 ) or (!blind and dexterity >= r)) playerHits = true;
                    else playerHits = false;
                    if (playerHits)
                    {
                        vendorHP -= weapon;
                        cout << "\nYou hit the evil " << enemy << "!\n\n";;
                    }
                    else
                    {
                        cout << "\nYou missed, too bad!\n";
                    }
                    if (vendorHP <= 0)
                    {
                        r = rnd(1000); // GP's

                        cout << "A vendor lies dead at your feet!\n\n"
                             << "You get all his wares :\n"
                             << "Plate armor\n"
                             << "A sword\n"
                             << "A strength potion\n"
                             << "An intelligence potion\n"
                             << "A dexterity potion\n"
                             << "A lamp\n\n"
                             << "And you get his hoard of " << r << " GP's\n\n";
                        armor = 3;
                        weapon = 3;
                        getPotion(&strength);
                        getPotion(&dexterity);
                        getPotion(&intelligence);
                        lamp = true;

                        attackContinues = false;
                        castle.clearRoom(getLevel(),getRow(),getColumn());
                        return pair<bool,char>(true,choice);
                    }
                }
                else  // player's turn is skipped
                {
                    if (!weapon)
                        cout << "\n** Pounding on a vendor won't hurt it!!\n";
                    if (bookStuckToHands)
                        cout << "\n** You can't beat it to death with a book!\n\n";
                }
                vendorTurn();
                if (strength < 1)
                {
                    return pair<bool,char>(false,choice);  // player dies
                }
            }
            else if (choice == 'B')   // bribe
            {
                if (!countTreasures())
                {
                    cout << "All I want is your life!\n\n";
                    vendorTurn();
                    if (strength < 1)
                    {
                        return pair<bool,char>(false,choice);  // player dies
                    }
                }
                else
                {
                    // consider each treasure for a bribe
                    for (size_t i = 1; i <= 8; i++)
                    {
                        if (hasTreasure(i))
                        {
                            prompt = "\nI want the " + Treasure::Type[i] + ".  Will you give it to me? ";
                            choice = yourchoice(prompt,"YN",string("** Please answer Yes or No"));
                            if (choice == 'Y')
                            {
                                cout << "\nOk, just don't tell anyone else.\n\n";
                                return pair<bool,char>(true,choice);
                            }
                            else
                            {

                            }
                        }
                    }
                }
            }
            else if (choice == 'R')   // retreat
            {
                // vendor gets one last attack
                vendorTurn();
                if (strength <= 0) pair<bool,char>(false,choice);  // player dies
                cout << "\nYou have escaped!\n\n";
                prompt = "Do you want to go North, South, East, or West? ";
                choice = yourchoice(prompt,"NSEW",string("** Don't press your luck, ")+getRace()+"!\n");
                cout << endl;
                return pair<bool,char>(true,choice);
            }
            else
            {
            }
        }
        firstTimeThruLoop = false;
    }
    return pair<bool,char>(true,choice);
}

void Player::vendorTurn()
{
    bool hits;
    short damageAmount = 7;
    int r = rnd(7)+rnd(7)+rnd(7);
    if (blind && dexterity < (r + 3)) hits = true;
    else if (!blind && dexterity < r) hits = true;
    else hits = false;
    cout << "The vendor attacks!\n\n";
    // inflict damage
    if (hits)
    {
        strength -= damageAmount;
        armor_durability -= min(damageAmount,armor);
        cout << "Ouch!  He hit you!\n";
        if (armor_durability <= 0)
        {
            cout << "Your armor has been destroyed . . . Good luck!\n\n";
            armor = 0;
            armor_durability = 0;
        }
    }
    else
    {
        cout << "\nWhat luck, he missed you!\n";
    }
}

short   Player::getRandomTreasure() const
{
    vector<short> myTreasures;
    for (short i = 0; i < 9; ++i)
    {
        if (treasures.test(i)) myTreasures.push_back(i);
    }
    if (myTreasures.size() == 0) return 0;
    if (myTreasures.size() == 1) return myTreasures[0];
    return myTreasures[rand()%myTreasures.size()];
}

void Player::openBook()
{
    cout << "\nYou open the book and ";
    switch (rand()%6)
    {
    case 0:
        cout << "\nFlash!  Oh no! You are now a blind " << getRace() << "!\n\n";
        blind = true;
        if (hasTreasure(4))
        {
            cout << "Oh!!  Your Opal Eye cures the blindness - you lucky " << getRace() << "!\n\n";
            blind = false;
        }
        break;
    case 1:
        cout << "\nit's another book of Zot's poetry! - Yech!!\n\n";
        break;
    case 2:
        cout << "\nit's an old copy of Play" << Monster::Type[rand()%12+1] << "\n\n";
        break;
    case 3:
        cout << "\nit's a Manual of Dexterity!\n\n";
        dexterity = 18;;
        break;
    case 4:
        cout << "\nit's a Manual of Strength!\n\n";
        strength = 18;
        break;
    case 5:
        cout << "\nThe book sticks to your hands - now you are unable to draw your weapon!\n\n";
        bookStuckToHands = true;
        if (hasTreasure(6))
        {
            cout << "Whew!!! The Blue Flame dissolves the book\n\n";
            bookStuckToHands = false;
        }
        break;
    default:
        ;
    }
    clearRoom();
}

bool Player::openChest()
{
    short moreGold;
    cout << "\nYou open the chest and ";
    switch (rnd(4))
    {
    case 1:
        cout << "\nkaboom!  It explodes!\n\n";
        damage(rand()%6+1);
        clearRoom();
        break;
    case 2:
        cout << "\nGas!!  You stagger from the room!\n\n";
        turns += 20;  // add 20 to the turn counter
        clearRoom();
        move("NSEW"[rand()%4]);
        currentRoom()->setExplored();
        return true;
    case 3:
    case 4:
        moreGold = rand() % 1000 +1;
        cout << "find " << moreGold << " gold pieces!\n\n";
        gold += moreGold;
        clearRoom();
    default:
        ;
    }
    return false;
}

// returns roomtype, X if exiting castle
Location Player::move(char type)
{
    Location ent(0,0,3);

    switch (type)
    {
    case 'N':
        if (location != ent)
        {
            location.decRow();
        }
        else  // exit castle
        {
            exit();
            return ExitCastle;
        }
        break;
    case 'S':
        location.incRow();
        break;
    case 'E':
        location.incColumn();
        break;
    case 'W':
        location.decColumn();
    default:
        ;
    }
    currentRoom()->setExplored();
    return location;
}

void Player::drink()
{
    short result = rand() % 8;
    short amount = rnd(3);
    cout << "\nYou take a drink and ";
    switch (result)
    {
    case 0:
        cout << "feel stronger";
        incrementStrength(amount);
        break;
    case 1:
        cout << "feel weaker";
        decrementStrength(amount);
        break;
    case 2:
        cout << "feel smarter";
        incrementIntelligence(amount);
        break;
    case 3:
        cout << "feel dumber";
        decrementIntelligence(amount);
        break;
    case 4:
        cout << "feel nimbler";
        incrementDexterity(amount);
        break;
    case 5:
        cout << "feel clumbsier";
        decrementDexterity(amount);
        break;
    case 6:
        cout << "become a ";
        changeRace();
        cout << getRace();
        break;
    case 7:
        cout << "turn into a ";
        changeSex();
        cout << (getSex()=='M'?"male":"female") << ' ' << getRace();
    default:
        ;
    }
    cout << "\n\n";
}

void Player::cheat()
{
    strength = intelligence = dexterity = 18;
    gold = 20000;
}

void Player::exit()
{
    cout << "\n************************************************************************\n\n";

    if (hasOrbOfZot)
    {
        cout << "You left the castle with the Orb of Zot.\n\n\n"
             << "An incredibly glorious victory!!\n\n"
             << "In addition, you got out with the following:\n"
             << "Your miserable life\n";
        for (size_t i = 1; i <= 8; ++i)
        {
            if (hasTreasure(i)) cout << "The " << Treasure::Type[i] << endl;
        }
        cout << Weapon[weapon] << " and " << Armor[armor] << endl;
        cout << "You also had " << flares << " flares and " << gold << " gold pieces\n\n";
        cout << "And it took you " << turns << " turns\n" << endl;
    }
    else
    {
        cout << "You left the castle without the Orb of Zot.\n\n\n"
             << "A less that awe-inspiring defeat.\n\n"
             << "When you left the castle, you had :\n"
             << "Your miserable life!\n";
        for (size_t i = 1; i <= 8; ++i)
        {
            if (hasTreasure(i)) cout << "The " << Treasure::Type[i] << endl;
        }
        cout << Weapon[weapon] << " and " << Armor[armor] << endl;
        cout << "You also had " << flares << " flares and " << gold << " gold pieces\n\n";
        cout << "And it took you " << turns << " turns!\n" << endl;
    }
}

