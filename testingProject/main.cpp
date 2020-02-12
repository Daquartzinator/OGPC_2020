#include<iostream>
#include<string>
#include<sstream>
#include<SFML/Graphics.hpp>
#include "crewmember.h"
#include "managementlib.h"
#include "interactobject.h"
using namespace std;
using namespace sf;

int main(){
    /** General Variables **/
    bool collision(Sprite, Sprite);
    bool upHeld = false;
    bool downHeld = false;
    bool leftHeld = false;
    bool rightHeld = false;
    bool aHeld = false;
    bool bHeld = false;

    Font font;
    Text box1Text, box2Text;
    Texture SpriteSheet;

    Sprite bigBorder, Area1, Area2, Area3, Employee;

    int temporaryArray[2] = {0, 64};
    AnimatedSprite Player(2, 400, temporaryArray, 32, 64);
    Player.sprite.setTexture(SpriteSheet);

    AnimatedSprite PlayerTruck(2, 400, temporaryArray, 32, 64);

    temporaryArray[1] = 32;
    InteractObject Goose(2, 496, temporaryArray, 32, 32);
    Goose.sprite.setPosition(355,160);
    Goose.sprite.setTexture(SpriteSheet);

    InteractObject Computer(2, 432, temporaryArray, 64, 32);
    Computer.sprite.setPosition(10,30);
    Computer.sprite.setTexture(SpriteSheet);

    InteractObject Plant(4, 576, temporaryArray, 32, 48);
    Plant.sprite.setPosition(140, 270);
    Plant.sprite.setTexture(SpriteSheet);

    string charities[3] = {"Homeless Shelter", "Health Awareness", "Clean Energy"};
    string charityDescrip[3] = {"Donate to help the homeless!\nYou will get more \"employees\".",
                                "Donate to improve Health Awareness!\nYour team will be healthier and stronger.",
                                "Donate to research into clean energy!\nYou will get insider prices on your upgrades."};
    int charityCount = 3;
    int currentSelection = 0;

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
    int portrait = 0; ///1=Barb, 2=Newt, 3=Larry.

    /** Player Control Variables **/
    bool playerControl = false;
    int xCoord = 50, yCoord = 50;
    int speed = 5;
    int temp = 0;

    /** Driving mission Variables **/
    bool drivingMission = false;

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
 /*UP*/             if (event.key.code == Keyboard::Up && !upHeld){
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
 /*DOWN*/           } else if (event.key.code == Keyboard::Down && !downHeld){
                    downHeld = true;\
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
 /*LEFT*/           } else if (event.key.code == Keyboard::Left && !leftHeld){
                    leftHeld = true;
                    if (management && !members[currentSelection].selected){
                        members[currentSelection].currentPayNext -= 10;
                        moneyUsed -= 10;
                        manageStatus = managementUpdate(currentSelection, members, money, expenses, moneyUsed, memberCount, &box1Text, &box2Text);
                    }
 /*RIGHT*/          } else if (event.key.code == Keyboard::Right && !rightHeld){
                    rightHeld = true;
                    if (management && !members[currentSelection].selected){
                        members[currentSelection].currentPayNext += 10;
                        moneyUsed += 10;
                        manageStatus = managementUpdate(currentSelection, members, money, expenses, moneyUsed, memberCount, &box1Text, &box2Text);
                    }
 /*A*/              } else if (event.key.code == Keyboard::A && !aHeld){
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
                    } else if (playerControl){
                        if (Computer.near){
                            modeSwitch(&playerControl, &shootSelectScreen, &currentSelection, members, memberCount);
                            shootoutSelectUpdate(currentSelection, members, memberCount, shootoutPeople, &shootoutSelected, &box1Text, &box2Text);
                        } else if (Goose.near){
                            cout << "HONK" << endl;
                        }
                    }
 /*B*/              } else if (event.key.code == Keyboard::B && !bHeld){
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
        if (!start){                         ///Switch between portraits based on which employee you're looking at
            for(int i = 0; i<3; i++){
                if (currentSelection == i){
                    portrait = 48*i;
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

            if (!start){
                Employee.setTexture(SpriteSheet);
                Employee.setPosition(220,20);
                Employee.setScale(2,2);
                Employee.setTextureRect(IntRect(528,portrait,48,48));
            }

            window.clear(Color::Black);
            window.draw(Area1);
            window.draw(Area2);
            window.draw(Area3);
            window.draw(box1Text);
            window.draw(box2Text);
            window.draw(Employee);

            window.display();
        }
        else if (playerControl){

            bigBorder.setTexture(SpriteSheet);
            bigBorder.setPosition(0,0);
            bigBorder.setTextureRect(IntRect(0,200,400,200));

            if (upHeld){
                yCoord = yCoord - speed;
            } else if (downHeld){
                yCoord= yCoord + speed;
            } else if (leftHeld){
                xCoord = xCoord - speed;
                temp = 0;
            } else if (rightHeld){
                xCoord = xCoord + speed;
                temp = 64;
            }

            if (collision(Player.sprite, Goose.sprite)){
                Goose.setFrame(1);
                Goose.near = true;
            }
            else if (collision(Player.sprite, Computer.sprite)){
                Computer.setFrame(1);
                Computer.near = true;
            }
            else {
                Goose.setFrame(0);
                Goose.near = false;
                Computer.setFrame(0);
                Computer.near = false;
            }

            Player.sprite.setPosition(xCoord,yCoord);

            window.clear(Color::Black);
            window.draw(bigBorder);
            window.draw(Computer.sprite);
            window.draw(Goose.sprite);
            window.draw(Plant.sprite);
            window.draw(Player.sprite); //always draw player last so he is on top
            window.display();
        }
    }
}

bool collision(Sprite Obj1, Sprite Obj2){
    if (Obj1.getGlobalBounds().intersects(Obj2.getGlobalBounds())){
        return true;
    }
}
