#include<iostream>
#include "interactobject.h"
#include<stdlib.h>
#include<SFML/Graphics.hpp>
using namespace std;
using namespace sf;

/// sYArraySize MUST BE EQUAL TO #of indicies of sYArray !!
InteractObject::InteractObject(int sYArraySize, int sX, int* sYArray, int sWidth, int sHeight){
    near = false;
    onScreen = false;
    yArray = (int*) calloc(sYArraySize, sizeof(int));
    for (int i = 0; i < sYArraySize; i++){
        yArray[i] = sYArray[i];
    }
    sheetX = sX;
    width = sWidth;
    height = sHeight;
}

void InteractObject::setFrame(int frame){
    sprite.setTextureRect(IntRect(sheetX, yArray[frame], width, height));
}
