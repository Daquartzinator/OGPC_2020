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

    int getMorale();
    std::string getName();

    void updateMorale();
};

#endif // CREWMEMBER_H_INCLUDED
