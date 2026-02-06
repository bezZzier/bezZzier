    // includes

    #include <iostream>
    #include <SFML/Graphics.hpp>
    #include <vector>

    using namespace std;

    // variables

    int screenx = 800;
    int screeny = 600;

    sf::Vector2f temp = {0, 0};

    vector<sf::Vector2f> points = {};

    int main() {
    sf::RenderWindow window(sf::VideoMode(screenx, screeny), "BezZzier");

    while (window.isOpen())
    {
        window.clear(sf::Color::White);

        // 1. Prepare the line path
        sf::VertexArray line(sf::LineStrip, points.size());
        for (size_t i = 0; i < points.size(); i++)
        {
            line[i].position = points[i];
            line[i].color = sf::Color::Black;
        }

        // 2. Draw the line path once
        window.draw(line);

        // 3. Draw the circles on top
        for (size_t i = 0; i < points.size(); i++)
        {
            sf::CircleShape point(10.f);
            point.setFillColor(sf::Color::Black);
            // Centering the circle on the line point
            point.setPosition(points[i].x - 10.f, points[i].y - 10.f);
            window.draw(point);
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::MouseButtonPressed) {
                temp = sf::Vector2f(sf::Mouse::getPosition(window));
                cout << "x: " << temp.x << " y: " << temp.y << endl;
                points.push_back(temp);
            }
        }

        window.display();
    }

    return 0;
}