#include<iostream>
#include<sstream>
#include "crewmember.h"
using namespace std;

string managementUpdate(int c, CrewMember *cList, int money, int expenses, int moneyUsed, int memberCount){
    //cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    stringstream ss;
    bool allConfirm = true;
    for (int i = 0; i < memberCount; i++){
        if (cList[i].manageConfirm == false){
            allConfirm = false;
            break;
        }
    } if (!allConfirm){
        ss << "Total Money: " << money << "\nExpenses: " << expenses << "\nRemaining Money: " << money - moneyUsed << endl;
        ss << cList[c].getName() << "\n----------\nMorale: " << cList[c].getMorale() << "\nCurrent Pay: "
            << cList[c].currentPay;
        ss << "\n\nPay them: " << cList[c].currentPayNext << endl;
        if (!cList[c].manageConfirm){
            ss << "A to confirm.";
        } else {
            ss << "B to unconfirm.";
        }
    } else {
        if (money - moneyUsed < 0){
            ss << "You're using too much\nmoney! Press B to go back.";
        } else {
            ss << "A to confirm all.";
        }
    }
    return ss.str();
}
