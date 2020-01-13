#include<iostream>
#include<sstream>
#include<SFML/Graphics.hpp>
#include "crewmember.h"
using namespace std;
using namespace sf;

void managementUpdate(int c, CrewMember *cList, int money, int expenses, int moneyUsed, int memberCount, Text *box1, Text *box2){
    stringstream ss;
    stringstream ss2;
    bool allConfirm = true;
    for (int i = 0; i < memberCount; i++){
        if (cList[i].manageConfirm == false){
            allConfirm = false;
            break;
        }
    } if (!allConfirm){
        ss << "Total Money: $" << money << "\nExpenses: $" << expenses << "\nRemaining Money: $" << money - moneyUsed << endl;
        ss2 << cList[c].getName() << "\n----------\nMorale: " << cList[c].getMorale() << "\nCurrent Pay: $"
            << cList[c].currentPay;
        ss << "\n\nPay " << cList[c].getName() << ": $" << cList[c].currentPayNext << endl;
        if (!cList[c].manageConfirm){
            ss << "A to confirm.";
        } else {
            ss << "B to unconfirm.";
        }
    } else {
        if (money - moneyUsed < 0){
            ss << "You're using too much\nmoney! Press B to go back.";
            for(int i = 0; i < memberCount; i++){
                cList[i].manageConfirm = false;
            }
        } else {
            ss2 << "You will save $" << money - moneyUsed << " for next week.";
            ss2 << "\n\nA to confirm all.";
            for(int i = 0; i < memberCount; i++){
                cList[i].manageConfirm = false;
                ss << cList[i].getName() << ": $" << cList[i].currentPayNext << "\n";
            }
        }
    }
    box1->setString(ss.str());
    box2->setString(ss2.str());
}

void charityStartUpdate(int c, string *charityList, string *charityDescrip, int charityCount, Text *box1, Text *box2){
    stringstream ss;
    stringstream ss2;
    ss << "* CHOOSE YOUR CHARITY *\n-----------------------\n\n";
    for(int i = 0; i < charityCount; i++){
        if(i == c){
            ss << " > ";
        } else {
            ss << "   ";
        }
        ss << charityList[i] << "\n";
    }
    ss2 << charityDescrip[c];
    box1->setString(ss.str());
    box2->setString(ss2.str());
}
