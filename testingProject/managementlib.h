#ifndef MANAGEMENTLIB_H_INCLUDED
#define MANAGEMENTLIB_H_INCLUDED
using namespace std;
using namespace sf;

    /** update functions are called when a button is pressed, and display text on screen **/
int managementUpdate(int c, CrewMember *cList, int money, int expenses, int moneyUsed, int memberCount, Text *box1, Text *box2);
    /** management section update **/
void charityStartUpdate(int c, string *charityList, string *charityDescrip, int charityCount, Text *box1, Text *box2);
    /** start-of-game charity selection update **/
void shootoutSelectUpdate(int c, CrewMember *cList, int memberCount, int *membersSelected, int *selected, Text *box1, Text *box2);
    /** shootout update **/
void tauntLetterUpdate(string *letterContents, int letterLength, int n, Text *box1, Text *box2);
    /** letter reading update **/
void modeSwitch(bool *currentMode, bool *newMode, int *currentSelection, CrewMember *cList, int memberCount);
#endif // MANAGEMENTLIB_H_INCLUDED
