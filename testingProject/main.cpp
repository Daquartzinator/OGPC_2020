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
    bool upHeld = false;
    bool downHeld = false;
    bool leftHeld = false;
    bool rightHeld = false;
    bool aHeld = false;
    bool bHeld = false;
    Font font;
    Sprite bigBorder;
    Sprite Player, Computer, Goose;
    Texture SpriteSheet;
    Sprite Area1, Area2, Area3;
    string charities[3] = {"Homeless Shelter", "Health Awareness", "Clean Energy"};
    string charityDescrip[3] = {"Donate to help the homeless!\nYou will get more \"employees\".",
        "Donate to improve Health Awareness!\nYour team will be healthier and stronger.",
        "Donate to research into clean energy!\nYou will get insider prices on your upgrades."};
    int charityCount = 3;
    int currentSelection = 0;
    Text box1Text;
    Text box2Text;

    /** Crew members **/
    CrewMember member1(100, 100, "Barbara", "   ", 50, 5);
    CrewMember member2(100, 100, "Newt", "      ", 60, 4);
    CrewMember member3(100, 100, "Larry", "     ", 40, 7);
    CrewMember members[3] = {member1, member2, member3};
    int memberCount = 3;

    /** Start Variables **/
    bool start = true;

    /** Management Variables **/
    bool management = false;
    int manageStatus = 0;   ///0=in progress, 1=all confirmed, -1=failed, set every time by managementUpdate
    int money = 500;
    int expenses = 100;
    int moneyUsed = 400;

    /** Player Control Variables **/
    bool playerControl = false;
    int xCord = 50, yCord = 50;

    /** Shootout Variables **/
    bool shootSelectScreen = false;
    int shootoutPeople[3] = {-1, -1, -1};
    int shootoutSelected = 0;
    bool shootoutScreen = false;

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

	box2Text.setFont(font);
	box2Text.setCharacterSize(9);
	box2Text.setPosition(165,131);

	cout << "That's how Mafia Works" << endl;

    RenderWindow window(VideoMode(400,200), "That's How Mafia Works");
    window.setFramerateLimit(30);

    /** Start **/
    charityStartUpdate(0, charities, charityDescrip, charityCount, &box1Text, &box2Text);

    while (window.isOpen()){
        Event event;
        while (window.pollEvent(event)){
            if (event.type == Event::Closed){
                window.close();
            }

            if (event.type == Event::KeyPressed){ ///These ifs trigger once per key press
                if (event.key.code == Keyboard::Up && !upHeld){
                    upHeld = true;
                    if (management){ ///these statements determine what each key press does depending on mode
                        currentSelection = (currentSelection + memberCount - 1) % memberCount;
                        manageStatus = managementUpdate(currentSelection, members, money, expenses, moneyUsed, memberCount, &box1Text, &box2Text);
                    } else if (start){
                        currentSelection = (currentSelection + charityCount - 1) % charityCount;
                        charityStartUpdate(currentSelection, charities, charityDescrip, charityCount, &box1Text, &box2Text);
                    } else if (shootSelectScreen){
                        currentSelection = (currentSelection + memberCount - 1) % memberCount;
                        shootoutSelectUpdate(currentSelection, members, memberCount, shootoutPeople, &shootoutSelected, &box1Text, &box2Text);
                    }
                } else if (event.key.code == Keyboard::Down && !downHeld){
                    downHeld = true;
                    if (management){
                        currentSelection = (currentSelection + 1) % memberCount;
                        manageStatus = managementUpdate(currentSelection, members, money, expenses, moneyUsed, memberCount, &box1Text, &box2Text);
                    } else if (start){
                        currentSelection = (currentSelection + 1) % charityCount;
                        charityStartUpdate(currentSelection, charities, charityDescrip, charityCount, &box1Text, &box2Text);
                    } else if (shootSelectScreen){
                        currentSelection = (currentSelection + 1) % memberCount;
                        shootoutSelectUpdate(currentSelection, members, memberCount, shootoutPeople, &shootoutSelected, &box1Text, &box2Text);
                    }
                } else if (event.key.code == Keyboard::Left && !leftHeld){
                    leftHeld = true;
                    if (management && !members[currentSelection].selected){
                        members[currentSelection].currentPayNext -= 10;
                        moneyUsed -= 10;
                        manageStatus = managementUpdate(currentSelection, members, money, expenses, moneyUsed, memberCount, &box1Text, &box2Text);
                    }
                } else if (event.key.code == Keyboard::Right && !rightHeld){
                    rightHeld = true;
                    if (management && !members[currentSelection].selected){
                        members[currentSelection].currentPayNext += 10;
                        moneyUsed += 10;
                        manageStatus = managementUpdate(currentSelection, members, money, expenses, moneyUsed, memberCount, &box1Text, &box2Text);
                    }
                } else if (event.key.code == Keyboard::A && !aHeld){
                    aHeld = true;
                    if (management){
                        if (manageStatus == 0){
                            members[currentSelection].selected = true;
                            manageStatus = managementUpdate(currentSelection, members, money, expenses, moneyUsed, memberCount, &box1Text, &box2Text);
                        } else if (manageStatus == 1){ ///A on all confirm switches mode
                            for (int i = 0; i < memberCount; i++){
                                members[i].currentPay = members[i].currentPayNext;
                                members[i].updateMorale();
                            }
                            modeSwitch(&management, &playerControl, &currentSelection, members, memberCount);
                            shootoutSelectUpdate(currentSelection, members, memberCount, shootoutPeople, &shootoutSelected, &box1Text, &box2Text);
                        } else { ///A on failed same as B
                            currentSelection = 0;
                            manageStatus = managementUpdate(currentSelection, members, money, expenses, moneyUsed, memberCount, &box1Text, &box2Text);
                        }
                    } else if (shootSelectScreen){
                        if (shootoutSelected == 3){
                            modeSwitch(&playerControl, &management, &currentSelection, members, memberCount);
                            ///Not sure what happens here right now
                        } else if (!members[currentSelection].selected){
                            members[currentSelection].selected = true;
                            shootoutSelected++;
                            shootoutSelectUpdate(currentSelection, members, memberCount, shootoutPeople, &shootoutSelected, &box1Text, &box2Text);
                        }
                    } else if (start){
                        ///switch to management
                        modeSwitch(&start, &management, &currentSelection, members, memberCount);
                        manageStatus = managementUpdate(currentSelection, members, money, expenses, moneyUsed, memberCount, &box1Text, &box2Text);
                    }
                } else if (event.key.code == Keyboard::B && !bHeld){
                    bHeld = true;
                    if (management){
                        if (manageStatus != 0){ ///B does nothing if nobody is selected
                            currentSelection = 0; ///(this sets it back to confirm screen on fail/all confirm)
                        }
                        members[currentSelection].selected = false;
                        manageStatus = managementUpdate(currentSelection, members, money, expenses, moneyUsed, memberCount, &box1Text, &box2Text);
                    } else if (shootSelectScreen){
                        if (shootoutSelected == 3){
                            currentSelection = 0;
                            shootoutSelected = 0;
                        } else if (members[currentSelection].selected){
                            members[currentSelection].selected = false;
                            shootoutSelected--;
                        }
                        shootoutSelectUpdate(currentSelection, members, memberCount, shootoutPeople, &shootoutSelected, &box1Text, &box2Text);
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
        if (management || start || shootSelectScreen){
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
            window.draw(box2Text);

            window.display();
        }
        else if (playerControl){
            if (upHeld){
                yCord--;
            } else if (downHeld){
                yCord++;
            } else if (leftHeld){
                xCord--;
            } else if (rightHeld){
                xCord++;
            }
            bigBorder.setTexture(SpriteSheet);
            bigBorder.setPosition(0,0);
            bigBorder.setTextureRect(IntRect(0,200,400,200));

            Player.setTexture(SpriteSheet);
            Player.setPosition(xCord,yCord);//  -> \/ |-| I
            Player.setTextureRect(IntRect(400,0,32,64));

            Computer.setTexture(SpriteSheet);
            Computer.setPosition(5,5);//  -> \/ |-| I
            Computer.setTextureRect(IntRect(432,0,32,32));

            Goose.setTexture(SpriteSheet);
            Goose.setPosition(355,160);//  -> \/ |-| I
            Goose.setTextureRect(IntRect(464,0,32,32));

            window.clear(Color::Black);
            window.draw(bigBorder);
            window.draw(Player);
            window.draw(Computer);
            window.draw(Goose);
            window.display();
        }
    }
}
