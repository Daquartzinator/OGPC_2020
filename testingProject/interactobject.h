#ifndef INTERACTOBJECT_H_INCLUDED
#define INTERACTOBJECT_H_INCLUDED
#include<SFML/Graphics.hpp>
#include "animatedsprite.h"
using namespace sf;

class InteractObject {
private:
    int width;
    int height;
    int sheetX;
    int yArraySize;
    int * yArray;
public:
    Sprite sprite;
    bool onScreen;
    bool near;

    InteractObject(int sYArraySize, int sX, int * sYArray, int sWidth, int sHeight);

    void setFrame(int frame);
};

#endif // INTERACTOBJECT_H_INCLUDED
