#ifndef INTERACTOBJECT_H_INCLUDED
#define INTERACTOBJECT_H_INCLUDED
#include<SFML/Graphics.hpp>
#include "animatedsprite.h"
using namespace sf;

class InteractObject : public AnimatedSprite {
/*private:
    int width;
    int height;
    int sheetX;
    int yArraySize;
    int * yArray;*/
public:
    //Sprite sprite;
    //bool onScreen;
    bool near;

    InteractObject(int sYArraySize, int sX, int * sYArray, int sWidth, int sHeight)
        : AnimatedSprite(sYArraySize, sX, sYArray, sWidth, sHeight){
        near = false;
    }

    //void setFrame(int frame);
};

#endif // INTERACTOBJECT_H_INCLUDED
