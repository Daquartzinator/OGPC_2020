#include<iostream>
#include<SFML/Graphics.hpp>
#include "add.h"
using namespace std;
using namespace sf;

int main(){

    bool windowTextIn = true;
    bool playerControl = false;

    Texture SpriteSheet;
    if (!SpriteSheet.loadFromFile("spritesheet.png")){
        cout<<"spritesheet broken rip"<<endl;
	}
    Sprite Area1, Area2, Area3;
    Sprite bigBorder;

    Area1.setTexture(SpriteSheet);
    Area1.setPosition(0,0);
    Area1.setTextureRect(IntRect(0,0,150,200));

    Area2.setTexture(SpriteSheet);
    Area2.setPosition(150,0);
    Area2.setTextureRect(IntRect(150,0,250,116));

    Area3.setTexture(SpriteSheet);
    Area3.setPosition(150,116);
    Area3.setTextureRect(IntRect(150,116,250,94));

    bigBorder.setTexture(SpriteSheet);
    bigBorder.setPosition(0,0);
    bigBorder.setTextureRect(IntRect(0,200,400,200));


    string playerName;

	cout << "That's how Mafia Works" << endl;
	cout << "This is a prototype file" << endl;
	cout << "type your name, when you're done press enter." << endl;


    RenderWindow window(VideoMode(400,200), "That's How Mafia Works");
    window.setFramerateLimit(30);

    while (window.isOpen()){
        Event event;
        while (window.pollEvent(event)){
            if (event.type == Event::Closed){
                window.close();
            }

            if (event.type == Event::TextEntered && windowTextIn){

                if (event.text.unicode == 13){
                    windowTextIn = false;
                    playerControl = true;
                    cout << playerName << endl;
                } else if (event.text.unicode == 8){ //if 'enter' key pressed
                    playerName = playerName.substr(0, playerName.size()-1);
                } else {
                    playerName = playerName + (char)event.text.unicode;
                }
            }
        }
        if (windowTextIn == true){
            window.clear(Color::Black);
            window.draw(Area1);
            window.draw(Area2);
            window.draw(Area3);
            window.display();
        }
        else if (playerControl == true){
            window.clear(Color::Black);
            window.draw(bigBorder);
            window.display();
        }


    }
}
