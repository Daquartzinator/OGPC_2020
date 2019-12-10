#include<iostream>
#include<SFML/Graphics.hpp>
using namespace std;
using namespace sf;

int main(){
	cout << "That's how Mafia Works" << endl;
	cout << "This is a prototype file" << endl;

    RenderWindow window(VideoMode(400,200), "That's How Mafia Works");
    window.setFramerateLimit(30);
    while (window.isOpen()){
        Event event;
        while (window.pollEvent(event)){
            if (event.type == Event::Closed){
                window.close();
            }
        }
    }
}
