#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Castle.h"
#include "Player.h"
#include "Command.h"
using namespace std;

void intro();

int main()
{
    srand(static_cast<unsigned>(time(0)));
    bool gameOver = false;
    string prompt;
    char choice;
    Castle* castle;
    Player* player;
    Command* command;

    intro();
    do
    {
        castle = new Castle;
        castle->printCastleContents();  //  **************** this is for debugging
        player = new Player(*castle);
        //player -> cheat();            //  **************** this is for debugging

        command = new Command(*player, *castle);
        cout << "************************************************************************\n\n"
             << "Ok, " << player->getRace() << ", you are now entering the castle!\n";

        player->printLocation();
        player->printAttributes();
        cout << "Here you find " << player->currentRoom()->description() << ".\n\n";

        // Game loop
        while (!gameOver)
        {
            gameOver = command->get();
        }

        prompt = "\nAre you foolish enough to want to play again? ";
        choice = yourchoice(prompt,"YN","** Please answer Yes or No\n");
        delete castle;
        delete player;
        if (choice == 'Y') gameOver = false;
        else gameOver = true;
    }
    while (choice == 'Y');
    cout << "Maybe dumb " << player->getRace()<< " is not so dumb after all!\n" << endl;
}

void intro()
{
    cout << "************************************************************************" << endl << endl;
    cout << "                * * * THE WIZARD'S CASTLE * * *" << endl << endl;
    cout << "************************************************************************" << endl;
    cout << "MANY CYCLES AGO, IN THE KINGDOM OF N'DIC, THE GNOMIC" << endl;
    cout << "WIZARD ZOT FORGED HIS GREAT *ORB OF POWER*. HE SOON" << endl;
    cout << "VANISHED, LEAVING BEHIND HIS VAST SUBTERRANEAN CASTLE" << endl;
    cout <<  "FILLED WITH ESURIENT MONSTERS, FABULOUS TREASURES, AND" << endl;
    cout <<  "THE INCREDIBLE *ORB OF ZOT*. FROM THAT TIME HENCE, MANY" << endl;
    cout <<  "A BOLD YOUTH HAS VENTURED INTO THE WIZARD'S CASTLE. AS" << endl;
    cout << "OF NOW, *NONE* HAS EVER EMERGED VICTORIOUSLY! BEWARE!!" << endl << endl;
}

char yourchoice(const string& prompt, const string& allowable, const string& errormsg)
{
    bool ok = false;
    char choice = 'N';
    while (!ok)
    {
        cout << prompt;
        cin >> choice;
        choice = static_cast<char>(toupper(choice));
        if (allowable.find(choice)==string::npos)
        {
            cout << endl << errormsg << endl;
            ok = false;
        }
        else
            ok = true;
    }
    cout << endl;
    return choice;
}

short yourchoice(const std::string& prompt, int max)
{
    bool ok = false;
    short choice = 0;
    string strchoice;
    cout << prompt;
    while (!ok)
    {
        cin >> strchoice;
        try
        {
            choice = static_cast<short>(stoi(strchoice));
            if (choice < 0 or choice > max)
            {
                cout << "\n** " << prompt;
                //ok = false;
            }
            else
                ok = true;
        }
        catch (const invalid_argument&)
        {
            cout << "** If you don't want any, just type 0 (zero).\n";
            cout << "\n** " << prompt;
        }
    }
    cout << endl;
    return choice;
}
