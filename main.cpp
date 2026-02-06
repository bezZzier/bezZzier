// includes

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

// variables

int screenx = 800;
int screeny = 600;

vector<sf::Vector2f> points = { {0.f, 0.f}, {100.f, 100.f} };

int main() {
    sf::RenderWindow window(sf::VideoMode(screenx, screeny), "BezZzier");

    while (window.isOpen())
    {
        for (size_t i = 0; i < points.size(); i++)
        {
            cout << "printed because of point" << to_string(i) << endl;
        }

        // display window here

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        

        // reset window

        window.clear(sf::Color::White);
        window.display();
    }

    return 0;
}
