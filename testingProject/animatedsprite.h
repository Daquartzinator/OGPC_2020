#ifndef ANIMATEDSPRITE_H_INCLUDED
#define ANIMATEDSPRITE_H_INCLUDED
#include<SFML/Graphics.hpp>
using namespace sf;

class AnimatedSprite {
private:
    int width;
    int height;
    int sheetX;
    int yArraySize;
    int * yArray;
public:
    Sprite sprite;
    bool onScreen;

    AnimatedSprite(int sYArraySize, int sX, int* sYArray, int sWidth, int sHeight);

    void setFrame(int frame);
};

#endif // ANIMATEDSPRITE_H_INCLUDED
