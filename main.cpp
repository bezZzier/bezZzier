// includes

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

int screenx = 800;
int screeny = 600;

int main() {
    sf::RenderWindow window(sf::VideoMode(screenx, screeny), "BezZzier");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        window.display();
    }

    return 0;
}