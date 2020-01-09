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
    bool manageConfirm;

    CrewMember(int sCurrentPay, int sMorale, std::string sName);

    int getMorale();
    std::string getName();

    void updateMorale();
    /** update's CrewMember's morale according to the formula **/
};

#endif // CREWMEMBER_H_INCLUDED
