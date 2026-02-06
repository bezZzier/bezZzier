    // includes

    #include <iostream>
    #include <SFML/Graphics.hpp>
    #include <vector>

    using namespace std;

    // variables

    int screenx = 800;
    int screeny = 600;

    sf::Vector2f temp = {0, 0};

    vector<sf::Vector2f> points = { {0.f, 0.f}, {100.f, 100.f} };

    int main() {
        sf::RenderWindow window(sf::VideoMode(screenx, screeny), "BezZzier");

        while (window.isOpen())
        {
            window.clear(sf::Color::White);

            for (size_t i = 0; i < points.size(); i++)
            {
                sf::CircleShape shape(10.f);
                shape.setFillColor(sf::Color::Black);
                shape.setPosition(points[i]);
                window.draw(shape);
            }

            // display window here

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();

                if(event.type == sf::Event::MouseButtonPressed) {
                    temp = sf::Vector2f(sf::Mouse::getPosition(window));
                    std::cout << "x: " << to_string(temp.x) << " y: " << to_string(temp.y) << endl;
                    points.push_back({temp.x, temp.y});
                }
            }

            // reset window

            window.display();
            
        }

        return 0;
    }
