#include<iostream>
#include "crewmember.h"
using namespace std;

CrewMember::CrewMember(int sCurrentPay, int sMorale, string sName, string sNameWS, int sHP, int sAttack){
    morale = sMorale;
    currentPay = sCurrentPay;
    name = sName;
    nameWhiteSp = sNameWS;
    currentPayNext = currentPay;
    selected = false;
    attack = sAttack;
    maxHP = sHP;
    currentHP = sHP;
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

int CrewMember::getHP(){
    return maxHP;
}

int CrewMember::getAttack(){
    return attack;
}
