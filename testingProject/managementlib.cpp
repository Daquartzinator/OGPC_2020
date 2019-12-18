#include<iostream>
#include "crewmember.h"
using namespace std;

void managementUpdate(int c, CrewMember *cList, int money, int expenses, int moneyUsed, int memberCount){
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    bool allConfirm = true;
    for (int i = 0; i < memberCount; i++){
        if (cList[i].manageConfirm == false){
            allConfirm = false;
            break;
        }
    } if (!allConfirm){
        cout << "Total Money: " << money << "\nExpenses: " << expenses << "\nRemaining Money: " << money - moneyUsed << endl;
        cout << cList[c].getName() << "\n----------\nMorale: " << cList[c].getMorale() << "\nCurrent Pay: "
            << cList[c].currentPay;
        cout << "\n\nPay them: " << cList[c].currentPayNext << endl;
        if (!cList[c].manageConfirm){
            cout << "A to confirm.";
        } else {
            cout << "B to unconfirm.";
        }
    } else {
        if (money - moneyUsed < 0){
            cout << "You're using too much money! Press B to go back.";
        } else {
            cout << "A to confirm all.";
        }
    }
}
