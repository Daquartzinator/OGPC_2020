#include<iostream>
#include "day.h"
using namespace std;

Day::Day(string sNumWord, int sStartWeek, bool sEndWeek, int sBL, int sBR, int sBU, int sBD){
    numWord = sNumWord;
    startWeek = sStartWeek;
    endWeek = sEndWeek;
    missionComplete = false;
    missionBoundL = sBL;
    missionBoundR = sBR;
    missionBoundU = sBU;
    missionBoundD = sBD;
}
