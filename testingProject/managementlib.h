#ifndef MANAGEMENTLIB_H_INCLUDED
#define MANAGEMENTLIB_H_INCLUDED
using namespace std;
using namespace sf;

void managementUpdate(int c, CrewMember *cList, int money, int expenses, int moneyUsed, int memberCount, Text *box1);
    /** function that takes in variables from management section and returns them to text object **/
string charityStartUpdate(int c, string *charityList, int charityCount);
#endif // MANAGEMENTLIB_H_INCLUDED
