#include<iostream>
#include<string>
#include<sstream>
#include<SFML/Graphics.hpp>
#include "crewmember.h"
#include "managementlib.h"

using namespace std;
using namespace sf;


int main(){
    /** General Variables **/
    bool upHeld;
    bool downHeld;
    bool leftHeld;
    bool rightHeld;
    bool aHeld;
    bool bHeld;
    Font font;
    Sprite bigBorder;
    Texture SpriteSheet;
    Sprite Area1, Area2, Area3;

    /** Crew members **/
    CrewMember member1(100, 100, "Barbara");
    CrewMember member2(100, 100, "Newt");
    CrewMember member3(100, 100, "Larry");
    CrewMember members[3] = {member1, member2, member3};
    int memberCount = 3;

    /** Management Variables **/
    bool management = true;
    int money = 400;
    int expenses = 100;
    int moneyUsed = 350;
    //stringstream mss; // Management String Stream
    int currentCrewMember = 0;
    Text manageText;

    /** Player Control Variables **/
    bool playerControl = false;

    if (!font.loadFromFile("Consolas.ttf")){
        cout<<"font broken rip"<<endl;
    }
    if (!SpriteSheet.loadFromFile("spritesheet.png")){
        cout<<"sprite sheet broken rip"<<endl;
	}

    //mss << "Total Money: " << money << "\nExpenses: " << expenses << "\nRemaining Money: " << money - moneyUsed << endl;
    //string mu = mss.str();

	manageText.setFont(font);
	manageText.setString(managementUpdate(0, members, money, expenses, moneyUsed, memberCount));
	manageText.setCharacterSize(9);
	manageText.setPosition(15,25);

    bigBorder.setTexture(SpriteSheet);
    bigBorder.setPosition(0,0);
    bigBorder.setTextureRect(IntRect(0,200,400,200));

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
                        manageText.setString(managementUpdate(currentCrewMember, members, money, expenses, moneyUsed, memberCount));
                        //window.clear(Color::Black);
                        window.draw(manageText);
                        window.display();
                    }
                } else if (event.key.code == Keyboard::Down && !downHeld){
                    downHeld = true;
                    if (management){
                        members[currentCrewMember].currentPayNext -= 10;
                        moneyUsed -= 10;
                        manageText.setString(managementUpdate(currentCrewMember, members, money, expenses, moneyUsed, memberCount));
                    }
                } else if (event.key.code == Keyboard::Left  && !leftHeld){
                    leftHeld = true;
                    if (management){
                        currentCrewMember = (currentCrewMember + memberCount - 1) % 3;
                        manageText.setString(managementUpdate(currentCrewMember, members, money, expenses, moneyUsed, memberCount));

                    }
                } else if (event.key.code == Keyboard::Right && !rightHeld){
                    rightHeld = true;
                    if (management){
                        currentCrewMember = (currentCrewMember + 1) % 3;
                        manageText.setString(managementUpdate(currentCrewMember, members, money, expenses, moneyUsed, memberCount));
                    }
                } else if (event.key.code == Keyboard::A && !aHeld){
                    aHeld = true;
                    if (management){
                        members[currentCrewMember].manageConfirm = true;
                        manageText.setString(managementUpdate(currentCrewMember, members, money, expenses, moneyUsed, memberCount));
                    }
                } else if (event.key.code == Keyboard::B && !bHeld){
                    bHeld = true;
                    if (management){
                        members[currentCrewMember].manageConfirm = false;
                        manageText.setString(managementUpdate(currentCrewMember, members, money, expenses, moneyUsed, memberCount));
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
        if (management == true){
            Area1.setTexture(SpriteSheet);
            Area1.setPosition(0,0);
            Area1.setTextureRect(IntRect(0,0,150,200));

            Area2.setTexture(SpriteSheet);
            Area2.setPosition(150,0);
            Area2.setTextureRect(IntRect(150,0,250,116));

            Area3.setTexture(SpriteSheet);
            Area3.setPosition(150,116);
            Area3.setTextureRect(IntRect(150,116,250,94));

            window.clear(Color::Black);
            window.draw(Area1);
            window.draw(Area2);
            window.draw(Area3);
            window.draw(manageText);

            window.display();
        }
        else if (playerControl == true){
            window.clear(Color::Black);
            window.draw(bigBorder);
            window.display();
        }
    }
}
