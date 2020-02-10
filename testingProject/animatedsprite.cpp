#include "animatedsprite.h"
#include<SFML/Graphics.hpp>
#include<stdlib.h>
using namespace std;
using namespace sf;

AnimatedSprite::AnimatedSprite(int sYArraySize, int sX, int* sYArray, int sWidth, int sHeight){
    onScreen = false;
    yArray = (int*) calloc(sYArraySize, sizeof(int));
    for (int i = 0; i < sYArraySize; i++){
        yArray[i] = sYArray[i];
    }
    sheetX = sX;
    width = sWidth;
    height = sHeight;
    sprite.setTextureRect(IntRect(sheetX, yArray[0], width, height)); ///Construct to start on frame 0
}

void AnimatedSprite::setFrame(int frame){
    sprite.setTextureRect(IntRect(sheetX, yArray[frame], width, height));
}
