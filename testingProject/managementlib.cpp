#include<iostream>
#include "crewmember.h"
using namespace std;

void managementUpdate(int c, CrewMember *cList, int money, int expenses, int moneyUsed){
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

    cout << "Total Money: " << money << "\nExpenses: " << expenses << "\nRemaining Money: " << money - moneyUsed << endl;
    cout << cList[c].getName() << "\n----------\nMorale: " << cList[c].getMorale() << "\nCurrent Pay: "
        << cList[c].currentPay;
    cout << "\n\nPay them: " << cList[c].currentPayNext;
}
