#ifndef CREWMEMBER_H_INCLUDED
#define CREWMEMBER_H_INCLUDED
#include<iostream>

class CrewMember {
private:
    int morale;
    std::string name;
public:
    int currentPay;
    int currentPayNext;
    CrewMember(int sCurrentPay, int sMorale, std::string sName);
    void updateMorale();
    int getMorale();
    std::string getName();
};

#endif // CREWMEMBER_H_INCLUDED
