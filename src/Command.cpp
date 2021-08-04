#include "Command.h"
#include "Monster.h"
#include "Vendor.h"
#include "Empty.h"
#include "Curse.h"
#include "Treasure.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
//#include <conio.h>
using namespace std;

Command::Command(Player& ch, Castle& cast) : me(ch), castle(cast)
{ }

// Return true if game ends
bool Command::get()
{
    Location newLocation;
    Location currentLocation;
    if (rand() % 5 == 0) randomMessage();
    cout << "Enter your command : ";
    cin >> command;
    command[0] = toupper(command[0]);
    if (command.size() > 2) command.resize(2);
    if (command.size() > 1) command[1] = toupper(command[1]);
    lastCommand = command[0];
    if (command == "DR")
    {
        lastCommand = 'd';
        if (rm() == 'P') me.drink();
        else cout << "** No pool here\n\n";
    }
    else if (strchr("NSEW",command[0]))
    {
        currentLocation = me.getLocation();

        me.incrementTurns();

        newLocation = me.move(command[0]);
        if (newLocation == Player::ExitCastle) return true;  // exit castle?
        while (currentLocation != newLocation)
        {
            currentLocation = newLocation;
            newLocation = reactToNewRoom();
        }
    }
    else if (command[0] == 'U')
    {
        if (rm() != 'U')
            cout << "\n** There are no stairs going up from here!\n\n";
        else me.goUp();
        reactToNewRoom();
    }
    else if (command[0] == 'D')
    {
        if (rm() != 'D')
            cout << "\n** There are no stairs going down from here!\n\n";
        else me.goDown();
        reactToNewRoom();
    }
    else if (command[0] == 'H') help();
    else if (command[0] == 'L')
    {
        if (me.hasLamp()) lamp();
        else cout << "** You don't have a lamp, " << me.getRace() << "!\n\n";
    }
    else if (command[0] == 'M') map();
    else if (command[0] == 'F') flare();
    else if (command[0] == 'G')
    {
        if (rm() == 'O')
            gaze();
        else
            cout << "\n** It's hard to gaze without an orb!\n\n";
    }
    else if (command[0] == 'O')
    {
        if (rm() == 'B') me.openBook();
        else if (rm() == 'C')
        {
            if (me.openChest())  // true return means (gas) move to new location
            {
                for (auto i = 0u; i < 20; i++) me.incrementTurns();  // add 20 to the turn counter
                reactToNewRoom();
            }
        }
        else cout << "\n** The only thing you opened was your big mouth!\n\n";
    }
    else if (command[0] == 'T')  // teleport
    {
        cout << endl;
        lastCommand = 'T';
        if (me.hasRunestaff())
        {
            currentLocation = me.getLocation();
            short x, y, z;
            x = yourchoice("Level? ",8);
            y = yourchoice("Row? ",8);
            z = yourchoice("Column? ",8);
            me.setLevel(x-1);
            me.setRow(y-1);
            me.setColumn(z-1);
            newLocation = me.getLocation();
            while (currentLocation != newLocation)
            {
                currentLocation = newLocation;
                newLocation = reactToNewRoom();
            }
        }
        else
        {
            cout << "** You can't teleport without the Runestaff!\n\n";
        }
    }
    else if (command[0] == 'Q')
    {
        quit();
        return true;
    }
    else
    {
        cout << "\n** Silly " << me.getRace() << ", that wasn't a valid command!" << endl << endl;
    }

    if (ST() <= 0 or IQ() <= 0)
    {
        string deathCause;
        if (ST()<=0) deathCause = "strength";
        if (IQ()<=0) deathCause = "intelligence";
        cout << "*******************************************************************************\n\n"
             << "A noble effort, or formerly living " << me.getRace() << "!\n\n"
             << "You died from a lack of " << deathCause << ".\n\n"
             << "At the time you died, you had :\n"
             << me.getWeaponAsString() << " and " << armor() << "\n"
             << "You also had " << me.getFlares() << " flares and " << me.getGold() << " gold pieces\n\n"
             << "And it took you " << me.getTurns() << " turns\n\n";
        return true;
    }
    return false;
}

void Command::help() const
{
    system("Clear");
    cout <<  "*** WIZARD'S CASTLE COMMAND AND INFORMATION SUMMARY ***" << endl << endl;
    cout <<  "The following commands are available :" << endl << endl;
    cout <<  "H/elp     N/orth    S/outh    E/ast     W/est     U/p" << endl;
    cout <<  "D/own     DR/ink    M/ap      F/lare    L/amp     O/pen" << endl;
    cout <<  "G/aze     T/eleport Q/quit" << endl << endl;
    cout <<  "The contents of the rooms are as follows :" << endl << endl;
    cout <<  ". = empty room      B = book            C = chest" << endl;
    cout <<  "D = stairs down     E = entrance/exit   F = flares" << endl;
    cout <<  "G = gold pieces     M = monster         O = crystal orb" << endl;
    cout <<  "P = magic pool      S = sinkhole        T = treasure" << endl;
    cout <<  "U = stairs up       V = vendor          W = warp/orb" << endl << endl;
    cout <<  "The benefits of having treasures are :" << endl << endl;
    cout <<  "Ruby Red - avoid lethargy     Pale Pearl - avoid leech" << endl;
    cout <<  "Green Gem - avoid forgetting  Opal Eye - cures blindness" << endl;
    cout <<  "Blue Flame - dissolves books  Norn Stone - no benefit" << endl;
    cout <<  "Palantir - no benefit         Silmaril - no benefit" << endl << endl;
    cout <<  "Press return (enter) when ready to resume, " << me.getRace() << "."  << endl;
    // getch();
    cout << endl;
}

void Command::lamp() const
{
    if (me.isBlind())
        cout << "** You can't see anything, you dumb " << me.getRace() << "!\n\n";
    else
    {
        char direction;
        cout << "\nWhere do you want to shine the lamp (N,S,E,W)? ";
        cin >> direction;
        direction = toupper(direction);
        cout << endl;
        if (string("NSEW").find(direction) == string::npos)
        {
            cout << "** That's not a direction, " << me.getRace() << "!\n\n";
            return;
        }
        short l = me.getLevel();
        short r = me.getRow();
        short c = me.getColumn();
        switch (direction)
        {
        case 'N':
            r = (r + 7) % 8;
            break;
        case 'S':
            r = (r + 1) % 8;
            break;
        case 'E':
            c = (c + 1) % 8;
            break;
        case 'W':
            c = (c + 7) % 8;
            break;
        default:
            ;
        }
        cout << "The lamp shines into ( " << r+1 << " , " << c+1 << " } Level " << l+1 << " .\n\n";
        cout << "There you will find " << castle.getRoom(l,r,c)->description() << " .\n\n";
        castle.getRoom(l,r,c)->setExplored();
    }
}

void Command::map() const
{
    if (me.isBlind())
        cout << "** You can't see anything, you dumb " << me.getRace() << "!\n\n";
    else
        castle.printLevel(me);
}

void Command::flare() const
{
    if (me.isBlind())
        cout << "** You can't see anything, you dumb " << me.getRace() << "!\n\n";
    else if (!me.getFlares())
        cout << "** Hey, bright one, you're out of flares!\n\n";
    else
    {
        short mylev = me.getLevel();
        short myrow = me.getRow();
        short mycol = me.getColumn();
        short relativeRow, relativeCol;
        cout << endl;
        for (short row = -1; row <= 1; ++row)
        {
            relativeRow = (myrow + row + 8) % 8;
            for (short col = -1; col <= 1; ++col)
            {
                relativeCol = (mycol + col + 8) % 8;
                cout << ' ' << **(castle.getRoom(mylev,relativeRow,relativeCol)) << "   ";
                castle.getRoom(mylev,relativeRow,relativeCol)->setExplored();
            }
            cout << endl << endl;
        }
        me.printLocation();
        me.addFlares(-1);
    }
}

void Command::gaze()
{
    if (me.isBlind())
        cout << "** You can't see anything, you dumb " << me.getRace() << "!\n\n";
    else
    {
        short l,r,c;
        Room* randomRoom;
        cout << "\nYou see ";
        switch (rnd(6))
        {
        case 1:
            cout << "yourself in a bloody heap!\n\n";
            me.setStrength(ST()-(rand()%2 + 1));
            clearRoom();
            break;
        case 2:
            cout << "yourself becoming a " << Monster::Type[rand()%12+1] << ".\n\n";
            break;
        case 3:
            cout << "a " << Monster::Type[rand()%12+1] << " gazing back at you.\n\n";
            break;
        case 4:
            l = rnd(8);
            r = rnd(8);
            c = rnd(8);
            randomRoom = castle.getRoom(l-1,r-1,c-1);
            cout << "a " << randomRoom -> description() << " at ( " << r << " , " << c << " ) Level " << l << ".\n\n";
            randomRoom->setExplored();
            break;
        case 5:
            if (rnd(8) < 4)
            {
                short z = castle.findZot();
                l = z / 100 + 1;
                r = z % 100 / 10 + 1;
                c = z % 10 + 1;
            }
            else
            {
                l = rnd(8);
                r = rnd(8);
                c = rnd(8);
            }
            cout << "***The Orb of Zot*** at ( " << r << " , " << c << " ) Level " << l << ".\n\n";
            break;
        case 6:
            cout << "a soap opera rerun!\n\n";
        default:
            ;
        }
    }
}

void Command::randomMessage() const
{
    string text = "You ";
    const string sound[4] = {"a scream","footsteps","a wumpus","thunder"};
    switch (rnd(7))
    {
    case 1:
        text += (me.isBlind() ? "stepped on a frog" : "see a bat fly by");
        break;
    case 2:
        text += "hear " + sound[rand()%4];
        break;
    case 3:
        text += "sneezed";
        break;
    case 4:
        text += "stepped on a frog";
        break;
    case 5:
        text += "smell a " + Monster::Type[rand()%12+1] + " frying";
        break;
    case 6:
        text += "feel like you're being watched";
        break;
    case 7:
        text += "are playing Wizard's Castle";
    default:
        ;
    }
    cout << text << endl << endl;
}

void Command::quit()
{
    string yn;
    cout << "\nDo you really want to quit now? ";
    cin >> yn;
    yn = toupper(yn[0]);
    if (yn[0] != 'Y')
    {
        cout << "\nThen don't say that you do!\n";
        return;
    }
    else
    {
        if (me.getHasOrbOfZot())
        {

        }
        else
        {
            cout << "\nA less that awe-imspiring defeat.\n"
                 << "When you left the castle, you had :\n"
                 << "Your miserable life!\n"
                 << me.getWeaponAsString() << " and " << me.getArmor();
            if (me.hasLamp()) cout << "  and a lamp\n";
            cout << "You also had " << me.getFlares() << "flares and " << me.getGold() << " gold pieces\n\n";
            cout << "And it took you " << me.getTurns() << " turns!\n\n";
        }
    }
}

// return pointer to current room
Location Command::reactToNewRoom()
{
    short numFlares, numGold;
    //Room* ptrRoom = currentRoom();
    Treasure* ptrTreasure;
    char roomtype = rm();
    size_t curse;
    size_t treasure;
    if (!me.isBlind()) me.printLocation();
    me.printAttributes();
    cout << "Here you find ";
    if (roomtype == 'T') cout << "the ";
    cout << currentRoom()->description() << "." << endl << endl;
    switch (roomtype)
    {
    case '.':   // empty room
        // is room cursed?
        curse = currentRoom()->getCurse();
        if (curse)
        {
            cout << "You are cursed!!!  ";
            for (size_t i = 1; i <=3; i++)
            {
                if (curse == i && !me.hasTreasure(2*i - 1))
                {
                    cout << Curse::name[i] << endl << endl;
                    me.addCurse(i);
                }
            }
            currentRoom()->removeCurse();
        }
        break;
    case 'S':
        me.setLevel((me.getLevel()+1)%8);
        currentRoom()->setExplored();
        break;
    case 'B':
        break;
    case 'C':
        break;
    case 'O':
        break;
    case 'W':
        if (lastCommand == 'T')
        {
            // Does this warp contain the Orb of Zot
            if (!currentRoom()->hasTheOrbOfZot())
            {
                if (strchr("NSEW",lastCommand))
                {
                    currentRoom()->setExplored();
                    me.move(lastCommand);
                    break;
                }
            }
            else
            {
                cout << "Great unmitigated Zot!\n\n"
                     << "You just found the ***Orb of Zot***!\n\n"
                     << "The Runestaff has disappeared!\n\n";
                me.setOrbOfZot();
                break;
            }
        }
        if (currentRoom()->hasTheOrbOfZot())
        {
            if (lastCommand == 'N') me.setRow((me.getRow()+7)%8);
            if (lastCommand == 'S') me.setRow((me.getRow()+1)%8);
            if (lastCommand == 'E') me.setColumn((me.getColumn()+1)%8);
            if (lastCommand == 'W') me.setColumn((me.getColumn()+7)%8);
        }
        else
        {
            me.setLevel(rand()%8);
            me.setRow(rand()%8);
            me.setColumn(rand()%8);
            currentRoom()->setExplored();
        }
        break;
    case 'F':
        numFlares = rnd(3);
        me.addFlares(numFlares);
        cout << "You now have " << me.getFlares() << " .\n\n";
        clearRoom();
        break;
    case 'G':
        numGold = rnd(10);
        me.addGold(numGold);
        cout << "You now have " << me.getGold() << " .\n\n";
        clearRoom();
        break;
    case 'T':
        ptrTreasure = dynamic_cast<Treasure*>(currentRoom());
        treasure = ptrTreasure->getNumber();
        me.setTreasure(treasure);
        cout << "It's now yours!" << endl << endl;
        clearRoom();
        // Does the treasure cure blindness
        if (treasure == 4 and me.isBlind())
        {
            cout << "Wow, it's a miracle!  You can see again.  The Opal Eye has cured your blindness.\n\n";
            me.cureBlindness();
        }

        // Does the treasure dissolve the book stuck to the hand
        if (treasure == 6 and me.isBookStuckToHands())
        {
            cout << "Wow!  The Blue Flame dissolves the book stuck to your hands.\n\n";
            me.dissolveBookStuckToHands();
        }

        // Does this treasure remove a curse?
        for (size_t i = 1; i <= 3; i++)
        {
            if (treasure == 2*i-1 and me.hasCurse(i))
            {
                me.removeCurse(i);
                cout << "A curse has been lifted.\n\n";
                break;
            }
        }
        break;
    case 'V':
        vendor();
        break;
    case 'M':
        monster();
        break;
    default:
        ;
    }
    return me.getLocation();
}

void Command::vendor()
{
    string prompt = "You may trade with, attack, or ignore the vendor.\n\nYour choice? ";
    string selection;
    string errmsg;
    if (rnd(2)==1) errmsg = "** Silly " + me.getRace() + ", that wasn't a valid command!\n";
    else errmsg = "** Nice shot, " + me.getRace() + "!\n";
    char choice = yourchoice(prompt, "TAI",errmsg);
    pair<bool,char> attackReturn;

    if (choice == 'I')
    {
        return;
    }
    if (choice == 'A')
    {
        dynamic_cast<Vendor*>(me.currentRoom())->setAnger(true);
        attackReturn = me.attackVendor();
        if (attackReturn.second)
        {
            me.move(attackReturn.second);
            reactToNewRoom();
        }
    }
    if (choice == 'T')
    {
        if (me.countTreasures())
        {
            int sellingPrice;
            for (size_t i = 1; i < 8; i++)
            {
                if (me.getTreasures().test(i))
                {
                    sellingPrice = rnd(static_cast<short>(1500*i));
                    prompt = "Do you want to sell the " + Treasure::Type[i] + " for " + to_string(sellingPrice) + " GP's? ";
                    choice = yourchoice(prompt,"YN","** Please answer YES or NO\n");
                    if (choice == 'Y') me.sellTreasure(i,sellingPrice);
                }
            }
        }
        if (gp() < 1000)
        {
            cout << "You're too poor to trade, " << race() << ".\n\n";
        }
        else
        {
            if (gp() >= 1250)
            {
                me.buyArmor();
            }
            if (gp() >= 1250)
            {
                me.buyWeapon();
            }
            if (gp() >= 1000) me.buyPotion("Strength");
            if (gp() >= 1000) me.buyPotion("Dexterity");
            if (gp() >= 1000) me.buyPotion("Intelligence");
            if (gp() >= 1000 && !me.hasLamp()) me.buyLamp();
        }
        cout << endl;
    }
}

Location Command::monster()
{
    string prompt;
    string error;
    char choice;
    string name = currentRoom()->description();
    Monster* mp = dynamic_cast<Monster*>(currentRoom());
    short loopCount = 0;
    short webCount = 0;
    bool hit;
    bool monsterEncounter = true;
    bool playerTakesTurn = true;
    bool cantAttack = false;

    if (me.isLethargic() or me.isBlind() or DX() < rnd(9)+rnd(9))
        playerTakesTurn = false;

    while (monsterEncounter)
    {
        loopCount++;
        // player's turn
        if (playerTakesTurn)
        {
            prompt = "You're facing a " + name + "!\n\nYou may Attack or Retreat.\n";
            if (rnd(2)) prompt += "You can also attempt a Bribe.\n";
            if (loopCount == 1 and IQ() > 14) prompt += "You can also Cast a spell.\n";
            prompt += string("\nYour strength is " + to_string(ST()))
                      + " and your dexterity is " + to_string(DX()) + " .\n\nYour choice? ";
            choice = yourchoice(prompt,"ABCR","** Choose one of the options listed.\n");

            switch (choice)
            {
            case 'A':
                hit = false;
                if (me.getWeapon()== 0)
                {
                   cout << "** Pounding on a " << name << " will not hurt it!\n\n";
                   cantAttack = true;
                }
                else if (me.isBookStuckToHands())
                {
                    cout << "** You can't hurt a " << name << " with a book stuck to your hands, you dingbat!!!\n\n";
                    cantAttack = true;
                }
                else
                {
                    if (me.isBlind())
                    {
                        if (DX() >= rnd(20) + 3) hit = true;
                    }
                    else
                    {
                        if (DX() >= rnd(20)) hit = true;
                    }
                }
                if (hit)
                {
                    cout << "You hit the evil " << name << ".\n\n";
                    // cout << "Debug: weapon=" << me.getWeapon() << " Monster HP before=" << mp->getHP();
                    mp->setHP(mp->getHP()-me.getWeapon());
                    // debug cout << " Monster HP after=" << mp->getHP() << endl;
                }
                else if (cantAttack == false)
                {
                    cout << "You missed it!\n\n";
                }
                else
                {

                }
                if (mp->getHP() <= 0)
                {
                    monsterDies(name);
                    return me.getLocation();
                }
                break;
            case 'B':
                if (me.countTreasures()==0)
                {
                    cout << "All I want is your life!\n";
                }
                else
                {
                    int bribe = me.getRandomTreasure();
                    prompt = "\nI want the " + Treasure::Type[bribe] + ".  Will you give it to me? ";
                    choice = yourchoice(prompt,"YN","** Please answer YES or NO\n");
                    if (choice == 'Y')
                    {
                        cout << "Ok, just don't tell anyone else.\n\n";
                        return me.getLocation();
                    }
                }
                break;
            case 'C':
                if (loopCount > 1 or IQ() < 15)
                {
                    cout << "** You can't cast a spell now!\n\n";
                }
                else
                {
                    prompt = "\nWhich spell (Web, Fireball, Deathspell)? ";
                    choice = yourchoice(prompt,"WFD","** Try one of the options given.\n");
                    switch (choice)
                    {
                    case 'D':
                        if (IQ() < 15 + rnd(4))
                        {
                            cout << "Death . . . yours!\n" << endl;
                            me.setIntelligence(0);
                            return me.getLocation();
                        }
                        else
                        {
                            monsterDies(name);
                            return me.getLocation();
                        }
                    case 'F':
                        me.decrementIntelligence(1);
                        me.decrementStrength(1);
                        mp->setHP(mp->getHP()-(rnd(7)+rnd(7)));
                        break;
                    case 'W':
                        me.decrementStrength(1);
                        webCount = rnd(6)+1;
                    default:
                        ;
                    }
                }
                break;
            case 'R':
                if (webCount) decrementWebCount(webCount);
                monsterTurn(mp, webCount);
                if (ST() <= 0)
                {
                    return me.getLocation();
                }
                else
                {
                    cout << "You have escaped!\n\n";
                }
                error = "** Don't press your luck, " + me.getRace() + "!\n";
                choice = yourchoice("Do you want to go North, South, East or West? ","NSEW",error);
                me.move(choice);
                return me.getLocation();
            default:
                ;
            }
            // monster's turn
            monsterTurn(mp, webCount);
            if (ST() <= 0)
            {
                return me.getLocation();
            }
        }

        playerTakesTurn = true;
    }
    return me.getLocation();
}

void Command::monsterTurn(Monster* mp, short webCount)
{
    cout << "The " << mp->description() << " attacks!\n\n";
    if (webCount)
    {
        cout << "The " << mp->description() << " is stuck and can't attack now!\n\n";
        decrementWebCount(webCount);
        return;
    }
    bool hit = false;
    if (me.isBlind())
        hit = DX() < rnd(7) + rnd(7) + rnd(7) + 3;
    else
        hit = DX() < rnd(7) + rnd(7) + rnd(7);
    if (hit)
    {
        cout << "Ouch! he hit you!\n\n";
        //cout << "Debug: armor_durability before: " << me.getArmor_durability();
        me.damage(mp->getNumber());
        //cout << "  after: " << me.getArmor_durability() << endl;
        // for the gargoyle or dragon, there is a 1/8 chance of breaking the weapon
        if (mp && (mp->getNumber() == 9 or mp->getNumber() == 12) && (rnd(8)==1))  // monster
        {
            {
                cout << "\a\nOh no!  Your " << Player::Weapon[me.getWeapon()] << " broke!!!\n\n";
                me.setWeapon(0);
            }
        }
        if (me.getArmor() && me.getArmor_durability() <= 0)
        {
            cout << "\a\nOh no!  Your " << Player::Armor[me.getArmor()] << " is destroyed!!\n\n";
            me.setArmor(0);
        }
    }
    else
    {
        cout << "What luck, he missed you!\n\n";
    }
}

void Command::decrementWebCount(short& webCount)
{
    webCount--;
    if (webCount == 0) cout << "The web just broke!\n\n";
}

void Command::monsterDies(const string& name)
{
    short reward = rnd(1000);
    static bool FirstKill = true;
    static short turnCountSinceLastKill = 0;

    me.addGold(reward);
    cout << "A " << name << " lies dead at your feet!\n\n";
    if (FirstKill or me.getTurns() - turnCountSinceLastKill > 60)
    {
        FirstKill = false;
        turnCountSinceLastKill = me.getTurns();
        randomRecipe();
    }
    cout << "You now get his hoard of " << reward << " GP's\n\n";

    // Does the monster hold the Runestaff
    if (currentRoom()->hasTheRunestaff())
    {
        cout << "\aGreat Zot!  You've found the Runestaff!\n\n";
        me.setRunestaff();
    }

    clearRoom();
}


void Command::randomRecipe()
{
    const string suffix[8] = {"wich"," Stew"," Soup"," Burger"," Roast"," Munchy"," Taco"," Pie"};
    cout << "You spend an hour eating a ";
    cout << Monster::Type[rnd(12)] << suffix[rand()%8] << endl << endl;
}

std::string Command::race() const
{
    return me.getRace();
}

short Command::gp() const
{
    return me.getGold();
}

std::string Command::armor() const
{
    return me.getArmorAsString();
}

Room*& Command::currentRoom()
{
    return me.currentRoom();
}

Room* Command::currentRoom() const
{
    return me.currentRoom();
}
char Command::rm() const
{
    return currentRoom()->getAbbr();
}

short Command::ST() const
{
    return me.getStrength();
}

short Command::DX() const
{
    return me.getDexterity();
}

short Command::IQ() const
{
    return me.getIntelligence();
}

void Command::clearRoom() const
{
    me.clearRoom();
}
