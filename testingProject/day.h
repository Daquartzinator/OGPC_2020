#ifndef DAY_H_INCLUDED
#define DAY_H_INCLUDED
#include<iostream>
using namespace std;

class Day {
public:
    string numWord;
    int startWeek; ///If it's the start of a week, index of that week's letter. If not, it's -1
    bool endWeek;

    Day(std::string sNumWord, int sStartWeek, bool sEndWeek);
};

#endif // DAY_H_INCLUDED
