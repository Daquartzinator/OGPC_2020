#include<iostream>
#include<string>
#include<sstream>
#include<SFML/Graphics.hpp>
#include "crewmember.h"
#include "managementlib.h"
#include "interactobject.h"
#include "animatedsprite.h"
#include "day.h"
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
    stringstream ss;


    /** Day Setup **/
    int currentDay = 0;
    Day day1("ONE", 0, false, 150, 2750, 100, 100);
    Day day2("TWO", -1, false, 150, 2750, 100, 100);
    Day day3("THREE", -1, false, 150, 2750, 100, 100);
    Day day4("FOUR", -1, false, 150, 2750, 100, 100);
    Day day5("FIVE", -1, true, 150, 2750, 100, 100);
    Day day6("SIX", -1, false, 150, 2750, 100, 100);
    Day dayList[6] = {day1, day2, day3, day4, day5, day6};

    /** Charities **/
    string charities[3] = {"Homeless Shelter", "Health Awareness", "Clean Energy"};
    string charityDescrip[3] = {"Donate to help the homeless!\nYou will get more \"employees\".",
        "Donate to improve Health Awareness!\nYour team will be healthier and stronger.",
        "Donate to research into clean energy!\nYou will get insider prices on your upgrades."};
    int charityCount = 3;
    int currentSelection = 0;

    /** Views **/
    View playerControlView(FloatRect(0,0,400,200)); ///View used in playerControl
    View drivingMissionView(FloatRect(0,0,300,200)); ///View used in mission
    View area4View(FloatRect(-100,0,100,200)); ///View for "HUD" in mission

    /** Fonts and text **/
    Font font;
    Text box1Text, box2Text, box4Text;
    box1Text.setFont(font);
    box1Text.setCharacterSize(9);
    box1Text.setPosition(15,10);

    box2Text.setFont(font);
    box2Text.setCharacterSize(9);
    box2Text.setPosition(165,131);

    box4Text.setFont(font);
    box4Text.setCharacterSize(9);
    box4Text.setPosition(-85, 10);

    /** Sprites and such **/
    Texture SpriteSheet;
    Texture WorldSheet;
    Texture RoadSheet;

    Sprite bigBorder(SpriteSheet, IntRect(0,200,400,200));
    bigBorder.setPosition(0,0);
    Sprite Area1(SpriteSheet, IntRect(0,0,150,200));
    Area1.setPosition(0,0);
    Sprite Area2(SpriteSheet, IntRect(150,0,250,116));
    Area2.setPosition(150,0);
    Sprite Area3(SpriteSheet, IntRect(150,116,250,94));
    Area3.setPosition(150,116);
    Sprite Area4(SpriteSheet, IntRect(400,200,100,200));
    Area4.setPosition(-100,0);

    Sprite world(WorldSheet, IntRect(0,0,800,200));
    world.setPosition(0,0);
    Sprite road(RoadSheet, IntRect(0,0,3000,200));

    int temporaryArray[3] = {0, 64, -1};
    AnimatedSprite Player(2, 400, temporaryArray, 32, 64);
    Player.sprite.setTexture(SpriteSheet);

    AnimatedSprite PlayerTruck(2, 400, temporaryArray, 32, 64);
    PlayerTruck.sprite.setTexture(SpriteSheet);

    temporaryArray[1] = 48;
    temporaryArray[2] = 96;
    AnimatedSprite Employee(3, 528, temporaryArray, 48, 48);
    Employee.sprite.setTexture(SpriteSheet);
    Employee.sprite.setPosition(220,20);
    Employee.sprite.setScale(2,2);
    Employee.setFrame(0);

    temporaryArray[1] = 32;
    temporaryArray[2] = -1;
    InteractObject Goose(2, 496, temporaryArray, 32, 32);
    Goose.sprite.setPosition(355,160);
    Goose.sprite.setTexture(SpriteSheet);

    InteractObject Computer(2, 432, temporaryArray, 64, 32);
    Computer.sprite.setPosition(10,30);
    Computer.sprite.setTexture(SpriteSheet);

    /*InteractObject Calander(4, 576, temporaryArray, 32, 48);
    Calander.sprite.setPosition(161, 142);
    Calander.sprite.setTexture(SpriteSheet);*/

    int spriteCount = 5;
    AnimatedSprite *spriteList[spriteCount] = {&Employee, &Goose, &Computer, &Player, &PlayerTruck};
    ///Order in this array determines draw order

    /** Wall Collision Sprites**/
    Sprite Top(SpriteSheet, IntRect(0,600,800,20));
    Top.setPosition(0,0);

    Sprite Right(SpriteSheet, IntRect(640,600,32,200));
    Right.setPosition(630,0);

    Sprite Bottom(SpriteSheet, IntRect(0,795,800,4));
    Bottom.setPosition(0,195);

    Sprite Left(SpriteSheet, IntRect(0,600,4,200));
    Left.setPosition(0,0);

    Sprite MiddleL(SpriteSheet,IntRect(160,621,16,110));
    MiddleL.setPosition(160,0);

    Sprite MiddleR(SpriteSheet,IntRect(176,621,16,110));
    MiddleR.setPosition(176,0);

    Sprite MiddleB(SpriteSheet, IntRect(161,770,14,1));
    MiddleB.setPosition(161,140);

    /** Crew members **/
    CrewMember member1(100, 100, "Barbara", "   ", 50, 5);
    CrewMember member2(100, 100, "Newt", "      ", 60, 4);
    CrewMember member3(100, 100, "Larry", "     ", 40, 7);
    CrewMember members[3] = {member1, member2, member3};
    int memberCount = 3;

    /** Start Variables **/
    bool start = true;

    /** Day start Variables **/
    bool dayIntro = false;

    /** Management Variables **/
    bool management = false;
    int manageStatus = 0;   ///0=in progress, 1=all confirmed, -1=failed, set every time by managementUpdate
    int money = 500;
    int expenses = 100;
    int moneyUsed = 400;

    /** Player Control Variables **/
    bool playerControl = false;
    int xCoord = 184, yCoord = 68;
    int speed = 5;
    int playerXoffset = 16; ///these make up for the fact that Player's coords are top left corner
    int playerYoffset = 32;
    int playerBoundL = 200; ///these are the bounds where the view will no longer scroll
    int playerBoundR = 600;
    int playerBoundU = 100;
    int playerBoundD = 100;

    /** Driving mission Variables **/
    bool drivingMission = false;
    int truckXoffset = 16;
    int truckYoffset = 32;

    /** Shootout Variables **/
    bool shootSelectScreen = false;
    int shootoutPeople[3] = {-1, -1, -1};
    int shootoutSelected = 0;
    bool shootoutScreen = false;

    /** Letter Variables **/
    bool tauntLetter = false;
    int letterLengths[1] = {7};
    string letterMessages[1][7] = {
        "To whom it may concern,\n\n",
        "Well, well, well. I see there's someone\nelse who's come to try to usurp my business.\n\n",
        "I'm getting tired of doing this, but this\nwill end much worse for you than for me.\n\n",
        "The only way you could possibly outmatch me\nis if you MANAGED YOUR MONEY WELL...\n\n",
        "But that's impossible.\n\n",
        "I look forward to our... strictly\nprofessional relationship.\n\n",
        "Cordially,\nB. Mann, Large Corporation Enterprises, CEO"};

    /** Loading **/
    if (!font.loadFromFile("Consolas.ttf")){
        cout<<"font broken rip"<<endl;
    }
    if (!SpriteSheet.loadFromFile("spritesheet.png")){
        cout<<"sprite sheet broken rip"<<endl;
	}
	if (!WorldSheet.loadFromFile("room.png")){
        cout << "room sheet broken. F" << endl;
	}
	if (!RoadSheet.loadFromFile("road.png")){
        cout << "road sheet is sad" << endl;
	}

    /** Setup **/
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
 /*UP*/         if (event.key.code == Keyboard::Up && !upHeld){
                    upHeld = true;
                    if (management){ ///these statements determine what each key press does depending on mode
                        currentSelection = (currentSelection + memberCount - 1) % memberCount;
                        Employee.setFrame(currentSelection);
                        manageStatus = managementUpdate(currentSelection, members, money, expenses, moneyUsed, memberCount, &box1Text, &box2Text);
                    } else if (start){
                        currentSelection = (currentSelection + charityCount - 1) % charityCount;
                        charityStartUpdate(currentSelection, charities, charityDescrip, charityCount, &box1Text, &box2Text);
                    } else if (shootSelectScreen){
                        currentSelection = (currentSelection + memberCount - 1) % memberCount;
                        Employee.setFrame(currentSelection);
                        shootoutSelectUpdate(currentSelection, members, memberCount, shootoutPeople, &shootoutSelected, &box1Text, &box2Text);
                    } else if (tauntLetter){
                        if (currentSelection > 0){
                            currentSelection--;
                        }
                        tauntLetterUpdate(letterMessages[dayList[currentDay].startWeek], letterLengths[dayList[currentDay].startWeek], currentSelection, &box1Text, &box2Text);
                    }
                } else if (event.key.code == Keyboard::Down && !downHeld){
                    downHeld = true;

 /*DOWN*/

                    if (management){
                        currentSelection = (currentSelection + 1) % memberCount;
                        Employee.setFrame(currentSelection);
                        manageStatus = managementUpdate(currentSelection, members, money, expenses, moneyUsed, memberCount, &box1Text, &box2Text);
                    } else if (start){
                        currentSelection = (currentSelection + 1) % charityCount;
                        charityStartUpdate(currentSelection, charities, charityDescrip, charityCount, &box1Text, &box2Text);
                    } else if (shootSelectScreen){
                        currentSelection = (currentSelection + 1) % memberCount;
                        Employee.setFrame(currentSelection);
                        shootoutSelectUpdate(currentSelection, members, memberCount, shootoutPeople, &shootoutSelected, &box1Text, &box2Text);
                    } else if (tauntLetter){
                        if (currentSelection < letterLengths[dayList[currentDay].startWeek] - 1 && currentSelection >= 0){
                            currentSelection++;
                        }
                        tauntLetterUpdate(letterMessages[dayList[currentDay].startWeek], letterLengths[dayList[currentDay].startWeek], currentSelection, &box1Text, &box2Text);
                    }
 /*LEFT*/       } else if (event.key.code == Keyboard::Left && !leftHeld){
                    leftHeld = true;
                    if (management && !members[currentSelection].selected){
                        members[currentSelection].currentPayNext -= 10;
                        moneyUsed -= 10;
                        manageStatus = managementUpdate(currentSelection, members, money, expenses, moneyUsed, memberCount, &box1Text, &box2Text);
                    }
 /*RIGHT*/      } else if (event.key.code == Keyboard::Right && !rightHeld){
                    rightHeld = true;
                    if (management && !members[currentSelection].selected){
                        members[currentSelection].currentPayNext += 10;
                        moneyUsed += 10;
                        manageStatus = managementUpdate(currentSelection, members, money, expenses, moneyUsed, memberCount, &box1Text, &box2Text);
                    }
 /*A*/          } else if (event.key.code == Keyboard::A && !aHeld){
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
                            currentDay++;
                            modeSwitch(&management, &dayIntro, &currentSelection, members, memberCount);
                            Employee.onScreen = false;
                            box1Text.setString("  DAY " + dayList[currentDay].numWord);
                            box2Text.setString("");
                        } else { ///A on failed same as B
                            currentSelection = 0;
                            manageStatus = managementUpdate(currentSelection, members, money, expenses, moneyUsed, memberCount, &box1Text, &box2Text);
                        }
                    } else if (dayIntro){
                        ///switch to letter reading
                        if (dayList[currentDay].startWeek == -1){
                            modeSwitch(&dayIntro, &playerControl, &currentSelection, members, memberCount);
                            Player.onScreen = true;
                            Goose.onScreen = true;
                            Computer.onScreen = true;
                        } else {
                            modeSwitch(&dayIntro, &tauntLetter, &currentSelection, members, memberCount);
                            Employee.onScreen = true;
                            currentSelection = -2;
                            tauntLetterUpdate(letterMessages[dayList[currentDay].startWeek], letterLengths[dayList[currentDay].startWeek], currentSelection, &box1Text, &box2Text);
                        }
                    } else if (shootSelectScreen){
                        if (shootoutSelected == 3){
                            //modeSwitch(&playerControl, &management, &currentSelection, members, memberCount);
                            ///Not sure what happens here right now
                        } else if (!members[currentSelection].selected){
                            members[currentSelection].selected = true;
                            shootoutSelected++;
                            shootoutSelectUpdate(currentSelection, members, memberCount, shootoutPeople, &shootoutSelected, &box1Text, &box2Text);
                        }
                    } else if (start){
                        ///Switch to day intro
                        modeSwitch(&start, &dayIntro, &currentSelection, members, memberCount);
                        box1Text.setString("  DAY " + dayList[currentDay].numWord);
                        box2Text.setString("");
                    } else if (tauntLetter){
                        if (currentSelection < 0){
                            currentSelection++;
                            tauntLetterUpdate(letterMessages[dayList[currentDay].startWeek], letterLengths[dayList[currentDay].startWeek], currentSelection, &box1Text, &box2Text);
                        }
                        if (currentSelection >= letterLengths[dayList[currentDay].startWeek] - 1){
                            modeSwitch(&tauntLetter, &playerControl, &currentSelection, members, memberCount);
                            Player.onScreen = true;
                            Goose.onScreen = true;
                            Computer.onScreen = true;
                            Employee.onScreen = false;
                        }
                    } else if (playerControl){
                        if (Computer.near){
                            /*modeSwitch(&playerControl, &shootSelectScreen, &currentSelection, members, memberCount);
                            Player.onScreen = false;
                            Goose.onScreen = false;
                            Computer.onScreen = false;
                            Employee.onScreen = true;
                            Employee.setFrame(0);
                            shootoutSelectUpdate(currentSelection, members, memberCount, shootoutPeople, &shootoutSelected, &box1Text, &box2Text);*/
                            if (!dayList[currentDay].missionComplete){
                                modeSwitch(&playerControl, &drivingMission, &currentSelection, members, memberCount);
                                Player.onScreen = false;
                                Goose.onScreen = false;
                                Computer.onScreen = false;
                                PlayerTruck.onScreen = true;
                            } else {
                                cout << "no" << endl;
                            }
                        } else if (Goose.near){
                            //modeSwitch(&playerControl, &drivingMission, &currentSelection, members, memberCount);
                            //Player.onScreen = false;
                            //Goose.onScreen = false;
                            //Computer.onScreen = false;
                            //cout << "HONK" << endl;
                            Player.onScreen = false;
                            Goose.onScreen = false;
                            Computer.onScreen = false;
                            if (dayList[currentDay].endWeek){
                                modeSwitch(&playerControl, &management, &currentSelection, members, memberCount);
                                Employee.onScreen = true;
                                manageStatus = managementUpdate(currentSelection, members, money, expenses, moneyUsed, memberCount, &box1Text, &box2Text);
                            } else {
                                modeSwitch(&playerControl, &dayIntro, &currentSelection, members, memberCount);
                                currentDay++;
                                box1Text.setString("  DAY " + dayList[currentDay].numWord);
                                box2Text.setString("");
                            }
                        }
                    }
 /*B*/          } else if (event.key.code == Keyboard::B && !bHeld){
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
        if (playerControl){
            if (upHeld){
                yCoord = yCoord - speed;
                if (collision(Player.sprite, Top)){
                    yCoord = yCoord + speed;
                }
                if (collision(Player.sprite, MiddleB)){
                    yCoord = yCoord + speed;
                }

            } else if (downHeld){
                yCoord= yCoord + speed;
                if (collision(Player.sprite, Bottom)){
                    yCoord = yCoord - speed;
                }
            } else if (leftHeld){
                xCoord = xCoord - speed;
                Player.setFrame(0);
                if (collision(Player.sprite, Left)){
                    xCoord = xCoord + speed;
                }
                if (collision(Player.sprite, MiddleR)){
                    xCoord = xCoord + speed;
                }
            } else if (rightHeld){
                xCoord = xCoord + speed;
                Player.setFrame(1);
                if (collision(Player.sprite, Right)){
                    xCoord = xCoord - speed;
                }
                 if (collision(Player.sprite, MiddleL)){
                    xCoord = xCoord - speed;
                }
            }
            playerControlView.setCenter(xCoord + playerXoffset, yCoord + playerYoffset);
            if (yCoord + playerYoffset < playerBoundU){
                playerControlView.setCenter(playerControlView.getCenter().x, playerBoundU);
            }
            if (xCoord + playerXoffset < playerBoundL){
                playerControlView.setCenter(playerBoundL, playerControlView.getCenter().y);
            }
            if (xCoord + playerXoffset > playerBoundR){
                playerControlView.setCenter(playerBoundR, playerControlView.getCenter().y);
            }
            if (yCoord + playerYoffset > playerBoundD){
                playerControlView.setCenter(playerControlView.getCenter().x, playerBoundD);
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


        } else if (drivingMission){
            if (upHeld){
                yCoord = yCoord - speed;
            } else if (downHeld){
                yCoord = yCoord + speed;
            } else if (leftHeld){
                xCoord = xCoord - speed;
                PlayerTruck.setFrame(0);
            } else if (rightHeld){
                xCoord = xCoord + speed;
                PlayerTruck.setFrame(1);
            }
            drivingMissionView.setCenter(xCoord + truckXoffset, yCoord + truckYoffset);
            if (yCoord + truckYoffset < dayList[currentDay].missionBoundU){
                drivingMissionView.setCenter(drivingMissionView.getCenter().x, dayList[currentDay].missionBoundU);
            }
            if (xCoord + truckXoffset < dayList[currentDay].missionBoundL){
                drivingMissionView.setCenter(dayList[currentDay].missionBoundL, drivingMissionView.getCenter().y);
            }
            if (xCoord + truckXoffset > dayList[currentDay].missionBoundR){
                drivingMissionView.setCenter(dayList[currentDay].missionBoundR, drivingMissionView.getCenter().y);
            }
            if (yCoord + truckYoffset > dayList[currentDay].missionBoundD){
                drivingMissionView.setCenter(drivingMissionView.getCenter().x, dayList[currentDay].missionBoundD);
            }
            PlayerTruck.sprite.setPosition(xCoord, yCoord);

            ss.str(string());
            ss << "\n\n\nPROGRESS\n ";
            for(int i = dayList[currentDay].missionBoundR/10; i <= xCoord; i += (dayList[currentDay].missionBoundR / 10)){
                ss << "_";
            }
            ss << "\n|";
            bool sl = false;
            for(int i = dayList[currentDay].missionBoundR/10; i <= dayList[currentDay].missionBoundR; i += (dayList[currentDay].missionBoundR / 10)){
                if (i <= xCoord){
                    ss << "X";
                } else if (!sl){
                    sl = true;
                    ss << "\\";
                } else {
                    ss << "_";
                }
            }
            ss << "|";
            if (xCoord >= 3000){
                modeSwitch(&drivingMission, &playerControl, &currentSelection, members, memberCount);
                dayList[currentDay].missionComplete = true;
                xCoord = 50;
                yCoord = 50;
                PlayerTruck.onScreen = false;
                Player.onScreen = true;
                Goose.onScreen = true;
                Computer.onScreen = true;
            } else if (xCoord >= dayList[currentDay].missionBoundR){
                ss << "\n\nMISSION SUCCESS.\n\nCONTINUE RIGHT";
            }
            box4Text.setString(ss.str());
        }
        window.clear(Color::Black);
        if (management || start || tauntLetter || shootSelectScreen || dayIntro){
            window.setView(window.getDefaultView());
            window.draw(Area1);
            window.draw(Area2);
            window.draw(Area3);
            window.draw(box1Text);
            window.draw(box2Text);
        } else if (playerControl){
            window.setView(playerControlView);
            window.draw(Right);
            window.draw(Left);
            window.draw(Top);
            window.draw(Bottom);
            window.draw(MiddleB);
            window.draw(MiddleR);
            window.draw(MiddleL);
            window.draw(world);
        } else if (drivingMission){
            window.setView(area4View);
            area4View.setViewport(FloatRect(0, 0, 0.25, 1));
            window.draw(Area4);
            window.draw(box4Text);
            window.setView(drivingMissionView);
            drivingMissionView.setViewport(FloatRect(0.25, 0, 0.75, 1));
            window.draw(road);
        }
        for (int i = 0; i < spriteCount; i++){
            if (spriteList[i]->onScreen){
                window.draw(spriteList[i]->sprite);
            }
        }
        window.display();
    }
}

bool collision(Sprite Obj1, Sprite Obj2){
    if (Obj1.getGlobalBounds().intersects(Obj2.getGlobalBounds())){
        return true;
    } else {
        return false;
    }
}
