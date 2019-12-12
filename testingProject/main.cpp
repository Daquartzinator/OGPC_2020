#include<iostream>
#include<SFML/Graphics.hpp>
#include "add.h"
using namespace std;
using namespace sf;

int main(){
    bool windowTextIn = true;
    bool playerControl = false;
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
                //cout << event.text.unicode << endl;
                if (event.text.unicode == 13){
                    windowTextIn = false;
                    cout << playerName << endl;
                } else if (event.text.unicode == 8){
                    playerName = playerName.substr(0, playerName.size()-1);
                } else {
                    playerName = playerName + (char)event.text.unicode;
                }
            }
        }
    }
}
