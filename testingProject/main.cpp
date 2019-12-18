#include<iostream>
#include<string>
#include<SFML/Graphics.hpp>
#include "crewmember.h"
#include "managementlib.h"

using namespace std;
using namespace sf;


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
    int expenses = 100;
    int moneyUsed = 350;

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
                        moneyUsed += 10;
                        managementUpdate(currentCrewMember, members, money, expenses, moneyUsed, memberCount);
                    }
                } else if (event.key.code == Keyboard::Down && !downHeld){
                    downHeld = true;
                    if (management){
                        members[currentCrewMember].currentPayNext -= 10;
                        moneyUsed -= 10;
                        managementUpdate(currentCrewMember, members, money, expenses, moneyUsed, memberCount);
                    }
                } else if (event.key.code == Keyboard::Left  && !leftHeld){
                    leftHeld = true;
                    if (management){
                        currentCrewMember = (currentCrewMember + memberCount - 1) % 3;
                        managementUpdate(currentCrewMember, members, money, expenses, moneyUsed, memberCount);
                    }
                } else if (event.key.code == Keyboard::Right && !rightHeld){
                    rightHeld = true;
                    if (management){
                        currentCrewMember = (currentCrewMember + 1) % 3;
                        managementUpdate(currentCrewMember, members, money, expenses, moneyUsed, memberCount);
                    }
                } else if (event.key.code == Keyboard::A && !aHeld){
                    aHeld = true;
                    if (management){
                        members[currentCrewMember].manageConfirm = true;
                        managementUpdate(currentCrewMember, members, money, expenses, moneyUsed, memberCount);
                    }
                } else if (event.key.code == Keyboard::B && !bHeld){
                    bHeld = true;
                    if (management){
                        members[currentCrewMember].manageConfirm = false;
                        managementUpdate(currentCrewMember, members, money, expenses, moneyUsed, memberCount);
                    }
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
        }
    }
}
