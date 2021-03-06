#include<iostream>
#include<sstream>
#include<SFML/Graphics.hpp>
#include "crewmember.h"
using namespace std;
using namespace sf;

int managementUpdate(int c, CrewMember *cList, int money, int expenses, int moneyUsed, int memberCount, Text *box1, Text *box2){
    stringstream ss;
    stringstream ss2;
    int manageStatus = 0;   ///returned val, 0=in progress, 1=all confirmed, -1=failed
    bool allConfirm = true;
    for (int i = 0; i < memberCount; i++){
        if (cList[i].selected == false){
            allConfirm = false;
            break;
        }
    }
    ss << "Total Money: $" << money << "\nExpenses: $" << expenses << "\n\n";
    for(int i = 0; i < memberCount; i++){
        if (!allConfirm && i == c){
            ss << ">";
        } else {
            ss << " ";
        }
        if (cList[i].selected){
            ss << "*";
        } else {
            ss << " ";
        }
        ss << cList[i].getName() << ": " << cList[i].getNameWhiteSp() << cList[i].currentPayNext << "\n";
    }
    ss << "\nRemaining Money: $" << money - moneyUsed << "\n\n";
    if (!allConfirm){
        ss2 << cList[c].getName() << "\n----------\nMorale: " << cList[c].getMorale() << "\nPaid $"
            << cList[c].currentPay << " last week.";
        if (!cList[c].selected){
            ss << "A to confirm.";
        } else {
            ss << "B to unconfirm.";
        }
    } else {
        if (money - moneyUsed < 0){
            ss2 << "You're using too much money!\n\nB to go back.";
            for(int i = 0; i < memberCount; i++){
                cList[i].selected = false;
            }
            manageStatus = -1;
        } else {
            ss2 << "You will save $" << money - moneyUsed << " for next week.";
            ss2 << "\n\nA to confirm all.";
            for(int i = 0; i < memberCount; i++){
                cList[i].selected = false;
            }
            manageStatus = 1;
        }
    }
    box1->setString(ss.str());
    box2->setString(ss2.str());
    return manageStatus;
}

void charityStartUpdate(int c, string *charityList, string *charityDescrip, int charityCount, Text *box1, Text *box2){
    stringstream ss;
    stringstream ss2;
    ss << "* CHOOSE YOUR CHARITY *\n-----------------------\n\n";
    for(int i = 0; i < charityCount; i++){
        if(i == c){
            ss << "> ";
        } else {
            ss << "  ";
        }
        ss << charityList[i] << "\n";
    }
    ss2 << charityDescrip[c];
    box1->setString(ss.str());
    box2->setString(ss2.str());
}

void shootoutSelectUpdate(int c, CrewMember *cList, int memberCount, int *membersSelected, int *selected, Text *box1, Text *box2){
    stringstream ss;
    stringstream ss2;
    ss << "* PREPARE FOR SHOOTOUT *\n\n";
    if (*selected == 3){
        ss << "Your team:\n\n";
        for(int i = 0; i < memberCount; i++){
            int j = 0;
            if (cList[i].selected){
                membersSelected[j] = i;
                j++;
            }
            cList[i].selected = false;
            ss << cList[i].getName() << "\n";
            if (j == 3)
                break;
        }
        ss2 << "A to confirm all.";
        //*selected = 0;
    } else {
        ss << "Choose " << 3 - *selected << " more.\n\n";
        for(int i = 0; i < memberCount; i++){
            if (c == i){
                ss << ">";
            } else {
                ss << " ";
            }
            if (cList[i].selected){
                ss << "*";
            } else {
                ss << " ";
            }
            ss << cList[i].getName() << "\n";
        }
        ss2 << cList[c].getName() << "\nHP: " << cList[c].currentHP << "/" << cList[c].getHP() << "\n";
        ss2 << "Attack: " << cList[c].getAttack();
    }
    box1->setString(ss.str());
    box2->setString(ss2.str());
}

void tauntLetterUpdate(string *letterContents, int letterLength, int n, Text *box1, Text *box2){
    stringstream ss;
    stringstream ss2;
    if (n == -2){
        ss2 << "               -----------\n               ** ALERT **\n               -----------";
    } else {
        if (n >= 0){
            if (n > 0){
                ss2 << letterContents[n - 1];
            }
            ss2 << letterContents[n];
            if (n == letterLength - 1){
                ss << "\n\nA to close the letter.";
            } else {
                ss << "\n\nU or D to read the letter.";
            }
        } else {
            ss << "\n\nA to open the letter.";
            ss2 << "YOU HAVE RECIEVED A LETTER FROM\nLARGE CORPORATION ENTERPRISES.";
        }
    }
    box1->setString(ss.str());
    box2->setString(ss2.str());
}

void modeSwitch(bool *currentMode, bool *nextMode, int *currentSelection, CrewMember *cList, int memberCount){
    *currentMode = false;
    *nextMode = true;
    *currentSelection = 0;
    for (int i = 0; i < memberCount; i++){
        cList[i].selected = false;
    }
}
