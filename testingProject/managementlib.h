#ifndef MANAGEMENTLIB_H_INCLUDED
#define MANAGEMENTLIB_H_INCLUDED
using namespace std;
using namespace sf;

    /** update functions are called when a button is pressed, and display text on screen **/
void managementUpdate(int c, CrewMember *cList, int money, int expenses, int moneyUsed, int memberCount, Text *box1, Text *box2);
    /** management section update **/
void charityStartUpdate(int c, string *charityList, string *charityDescrip, int charityCount, Text *box1, Text *box2);
    /** start-of-game charity selection update **/
void modeSwitch(bool *currentMode, bool *newMode, int *currentSelection);
#endif // MANAGEMENTLIB_H_INCLUDED
