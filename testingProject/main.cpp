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
public:
    int currentPay;
    CrewMember(int sCurrentPay);
    void updateMorale();
    int getMorale();
};

CrewMember::CrewMember(int sCurrentPay){
    morale = sCurrentPay;
    currentPay = sCurrentPay;
}

void CrewMember::updateMorale(){
    morale = (morale + currentPay)/2;
}

int CrewMember::getMorale(){
    return morale;
}

int main(){
    bool windowTextIn = true;

    bool management = false;
    bool playerControl = false;

    bool upHeld;
    bool downHeld;
    bool leftHeld;
    bool rightHeld;
    bool aHeld;
    bool bHeld;
    string playerTextIn = "";

    string playerName = "";

    int money = 400;

    CrewMember member1(100);

	cout << "That's how Mafia Works" << endl;

    RenderWindow window(VideoMode(400,200), "That's How Mafia Works");
    window.setFramerateLimit(30);
    while (window.isOpen()){
        Event event;
        while (window.pollEvent(event)){
            if (event.type == Event::Closed){
                window.close();
            }

            if (event.type == Event::KeyPressed){
                if (event.key.code == Keyboard::Up){
                    upHeld = true;
                } else if (event.key.code == Keyboard::Down){
                    downHeld = true;
                } else if (event.key.code == Keyboard::Left){
                    leftHeld = true;
                } else if (event.key.code == Keyboard::Right){
                    rightHeld = true;
                } else if (event.key.code == Keyboard::A){
                    aHeld = true;
                } else if (event.key.code == Keyboard::B){
                    bHeld = true;
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
