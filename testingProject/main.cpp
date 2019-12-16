#include<iostream>
#include<string>
#include<SFML/Graphics.hpp>
#include "add.h"
using namespace std;
using namespace sf;

/** Move the class to header later **/
class CrewMember {
private:
    int morale;
    string name;
public:
    int currentPay;
    int currentPayNext;
    CrewMember(int sCurrentPay, int sMorale, string sName);
    void updateMorale();
    int getMorale();
    string getName();
};

CrewMember::CrewMember(int sCurrentPay, int sMorale, string sName){
    morale = sMorale;
    currentPay = sCurrentPay;
    name = sName;
    currentPayNext = currentPay;
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

void managementUpdate(int c, CrewMember *cList){
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << cList[c].getName() << "\n----------\nMorale: "
        << cList[c].getMorale() << "\nCurrent Pay: "
        << cList[c].currentPay;
    cout << "\n\nPay them: " << cList[c].currentPayNext;
}

int main(){
    bool management = true;
    bool playerControl = false;

    bool upHeld;
    bool downHeld;
    bool leftHeld;
    bool rightHeld;
    bool aHeld;
    bool bHeld;

    int money = 400;

    int currentCrewMember = 0;

    CrewMember member1(100, 100, "Barbara");
    CrewMember member2(100, 100, "Newt");
    CrewMember member3(50, 100, "Larry");

    CrewMember members[3] = {member1, member2, member3};
    int memberCount = 3;

	cout << "That's how Mafia Works" << endl;

    RenderWindow window(VideoMode(400,200), "That's How Mafia Works");
    window.setFramerateLimit(30);
    while (window.isOpen()){
        Event event;
        while (window.pollEvent(event)){
            if (event.type == Event::Closed){
                window.close();
            }

            if (event.type == Event::KeyPressed){ ///These ifs trigger once per key press
                if (event.key.code == Keyboard::Up && !upHeld){
                    upHeld = true;
                    if (management){
                        members[currentCrewMember].currentPayNext += 10;
                        managementUpdate(currentCrewMember, members);
                    }
                } else if (event.key.code == Keyboard::Down && !downHeld){
                    downHeld = true;
                    if (management){
                        members[currentCrewMember].currentPayNext -= 10;
                        managementUpdate(currentCrewMember, members);
                    }
                } else if (event.key.code == Keyboard::Left  && !leftHeld){
                    leftHeld = true;
                    if (management){
                        currentCrewMember = (currentCrewMember + memberCount - 1) % 3;
                        managementUpdate(currentCrewMember, members);
                    }
                } else if (event.key.code == Keyboard::Right && !rightHeld){
                    rightHeld = true;
                    if (management){
                        currentCrewMember = (currentCrewMember + 1) % 3;
                        managementUpdate(currentCrewMember, members);
                    }
                } else if (event.key.code == Keyboard::A && !aHeld){
                    aHeld = true;
                } else if (event.key.code == Keyboard::B && !bHeld){
                    bHeld = true;
                }
            } else if (event.type == Event::KeyReleased){
                if (event.key.code == Keyboard::Up){
                    upHeld = false;
                } else if (event.key.code == Keyboard::Down){
                    downHeld = false;
                } else if (event.key.code == Keyboard::Right){
                    rightHeld = false;
                } else if (event.key.code == Keyboard::Left){
                    leftHeld = false;
                } else if (event.key.code == Keyboard::A){
                    aHeld = false;
                } else if (event.key.code == Keyboard::B){
                    bHeld = false;
                }
            }

            /*if (event.type == Event::TextEntered && windowTextIn){
                cout << event.text.unicode << endl;
                if (event.text.unicode == 13){  ///pressed enter
                    playerTextIn = "";
                    if (playerName == ""){
                        windowTextIn = false;
                        playerName = playerTextIn;
                        cout << playerName << endl;

                        management = true;
                        cout << "How much money do you want to pay crew member 1?\n";
                        cout << "You have $" << money << ".\n";
                    } else if (management){

                    }
                } else if (event.text.unicode == 8){ ///pressed backspace
                    playerTextIn = playerTextIn.substr(0, playerTextIn.size()-1);
                } else {
                    playerTextIn = playerTextIn + (char)event.text.unicode;
                }
            }*/
        }
    }
}
