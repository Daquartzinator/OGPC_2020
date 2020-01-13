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
    string charities[3] = {"Homeless Shelter", "Health Awareness", "Clean Energy"};
    int charityCount = 3;
    int currentSelection = 0;
    Text box1Text;

    /** Crew members **/
    CrewMember member1(100, 100, "Barbara");
    CrewMember member2(100, 100, "Newt");
    CrewMember member3(100, 100, "Larry");
    CrewMember members[3] = {member1, member2, member3};
    int memberCount = 3;

    /** Start Variables **/
    bool start = true;

    /** Management Variables **/
    bool management = false;
    int money = 400;
    int expenses = 100;
    int moneyUsed = 350;
    //int currentCrewMember = 0;

    /** Player Control Variables **/
    bool playerControl = false;

    /** Loading **/
    if (!font.loadFromFile("Consolas.ttf")){
        cout<<"font broken rip"<<endl;
    }
    if (!SpriteSheet.loadFromFile("spritesheet.png")){
        cout<<"sprite sheet broken rip"<<endl;
	}

	/** Setup **/
	box1Text.setFont(font);
	box1Text.setCharacterSize(9);
	box1Text.setPosition(15,25);

    bigBorder.setTexture(SpriteSheet);
    bigBorder.setPosition(0,0);
    bigBorder.setTextureRect(IntRect(0,200,400,200));

	cout << "That's how Mafia Works" << endl;

    RenderWindow window(VideoMode(400,200), "That's How Mafia Works");
    window.setFramerateLimit(30);

    /** Start **/
    charityStartUpdate(0, charities, charityCount, &box1Text);

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
                        members[currentSelection].currentPayNext += 10;
                        moneyUsed += 10;
                        managementUpdate(currentSelection, members, money, expenses, moneyUsed, memberCount, &box1Text);
                    } else if (start){
                        currentSelection = (currentSelection + charityCount - 1) % charityCount;
                        charityStartUpdate(currentSelection, charities, charityCount, &box1Text);
                        //box1Text.setString(charityStartUpdate(currentSelection, charities, charityCount));
                    }
                } else if (event.key.code == Keyboard::Down && !downHeld){
                    downHeld = true;
                    if (management){
                        members[currentSelection].currentPayNext -= 10;
                        moneyUsed -= 10;
                        managementUpdate(currentSelection, members, money, expenses, moneyUsed, memberCount, &box1Text);
                    } else if (start){
                        currentSelection = (currentSelection + 1) % charityCount;
                        charityStartUpdate(currentSelection, charities, charityCount, &box1Text);
                        //box1Text.setString(charityStartUpdate(currentSelection, charities, charityCount));
                    }
                } else if (event.key.code == Keyboard::Left  && !leftHeld){
                    leftHeld = true;
                    if (management){
                        currentSelection = (currentSelection + memberCount - 1) % memberCount;
                        managementUpdate(currentSelection, members, money, expenses, moneyUsed, memberCount, &box1Text);
                    }
                } else if (event.key.code == Keyboard::Right && !rightHeld){
                    rightHeld = true;
                    if (management){
                        currentSelection = (currentSelection + 1) % memberCount;
                        managementUpdate(currentSelection, members, money, expenses, moneyUsed, memberCount, &box1Text);
                    }
                } else if (event.key.code == Keyboard::A && !aHeld){
                    aHeld = true;
                    if (management){
                        members[currentSelection].manageConfirm = true;
                        managementUpdate(currentSelection, members, money, expenses, moneyUsed, memberCount, &box1Text);
                    } else if (start){
                        ///switch to management
                        currentSelection = 0;
                        start = false;
                        management = true;
                        managementUpdate(currentSelection, members, money, expenses, moneyUsed, memberCount, &box1Text);
                    }
                } else if (event.key.code == Keyboard::B && !bHeld){
                    bHeld = true;
                    if (management){
                        members[currentSelection].manageConfirm = false;
                        managementUpdate(currentSelection, members, money, expenses, moneyUsed, memberCount, &box1Text);
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
        if (management || start){
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
            window.draw(box1Text);

            window.display();
        }
        else if (playerControl == true){
            window.clear(Color::Black);
            window.draw(bigBorder);
            window.display();
        }
    }
}
