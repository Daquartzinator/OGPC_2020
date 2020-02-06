#ifndef INTERACTOBJECT_H_INCLUDED
#define INTERACTOBJECT_H_INCLUDED
#include<SFML/Graphics.hpp>
using namespace sf;

class InteractObject {
private:
    Sprite sprite;
    int width;
    int height;
    int sheetX;
    int yArraySize;
    int * yArray;
public:
    bool near;

    InteractObject(int sYArraySize, int sX, int * sYArray, int sWidth, int sHeight);
};

#endif // INTERACTOBJECT_H_INCLUDED
