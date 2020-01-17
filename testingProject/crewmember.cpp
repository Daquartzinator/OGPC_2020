#include<iostream>
#include "crewmember.h"
using namespace std;

CrewMember::CrewMember(int sCurrentPay, int sMorale, string sName, string sNameWS){
    morale = sMorale;
    currentPay = sCurrentPay;
    name = sName;
    nameWhiteSp = sNameWS;
    currentPayNext = currentPay;
    manageConfirm = false;
}

void CrewMember::updateMorale(){
    morale = (morale + currentPay)/2;
}

int CrewMember::getMorale(){
    return morale;
}

string CrewMember::getName(){
    return name;
}

string CrewMember::getNameWhiteSp(){
    return nameWhiteSp;
}
