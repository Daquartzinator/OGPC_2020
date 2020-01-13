#ifndef MANAGEMENTLIB_H_INCLUDED
#define MANAGEMENTLIB_H_INCLUDED
using namespace std;
using namespace sf;

void managementUpdate(int c, CrewMember *cList, int money, int expenses, int moneyUsed, int memberCount, Text *box1, Text *box2);
    /** function that takes in variables from management section and returns them to text object **/
void charityStartUpdate(int c, string *charityList, string *charityDescrip, int charityCount, Text *box1, Text *box2);
#endif // MANAGEMENTLIB_H_INCLUDED
