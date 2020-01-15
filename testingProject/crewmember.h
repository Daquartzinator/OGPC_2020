#ifndef CREWMEMBER_H_INCLUDED
#define CREWMEMBER_H_INCLUDED
#include<iostream>

class CrewMember {
private:
    int morale;
    std::string name;
    //int nameLenNeg;     /** Max name length (10) - name length **/
    std::string nameWhiteSp; /** Whitespace string, length = max name length (10) - name length **/
public:
    int currentPay;
    int currentPayNext;
    bool manageConfirm;

    CrewMember(int sCurrentPay, int sMorale, std::string sName, std::string sNameWS);

    int getMorale();
    std::string getName();
    std::string getNameWhiteSp();

    void updateMorale();
    /** update's CrewMember's morale according to the formula **/
};

#endif // CREWMEMBER_H_INCLUDED
