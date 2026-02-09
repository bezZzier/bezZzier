#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

// variables

int screenx = 1920;
int screeny = 1080;

sf::Vector2f tempmousepos = {0, 0};

vector<sf::Vector2f> points = {};

sf::Vector2f lerp(sf::Vector2f a, sf::Vector2f b, float t) {
    return a + t * (b - a);
}

sf::Vector2f getBezierPoint(vector<sf::Vector2f> p, float t) {
    while (p.size() > 1) {
        vector<sf::Vector2f> next_points;
        for (size_t i = 0; i < p.size() - 1; i++) {
            next_points.push_back(lerp(p[i], p[i + 1], t));
        }
        p = next_points;
    }
    return p[0];
}

int main() {
    sf::RenderWindow window(sf::VideoMode(screenx, screeny), "BezZzier");

    while (window.isOpen())
    {
        sf::Vector2f mousepos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        
        window.clear(sf::Color::White);

        sf::VertexArray line(sf::LineStrip, points.size());
        for (size_t i = 0; i < points.size(); i++)
        {
            line[i].position = points[i];
            line[i].color = sf::Color(200, 200, 200);
        }
        window.draw(line);

        if (points.size() >= 2) {
            sf::VertexArray curve(sf::LineStrip);
            for (float t = 0.f; t <= 1.f; t += 0.01f) {
                sf::Vector2f cp = getBezierPoint(points, t);
                curve.append(sf::Vertex(cp, sf::Color::Red));
            }
            window.draw(curve);
        }   

        for (size_t i = 0; i < points.size(); i++)
        {
            sf::CircleShape point(10.f);
            point.setFillColor(sf::Color::Black);
            point.setOrigin(10.f, 10.f);
            point.setPosition(points[i]);
            window.draw(point);
        }

        // display window here

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Left) {
                    tempmousepos = sf::Vector2f(sf::Mouse::getPosition(window));
                    points.push_back(tempmousepos);
                }
                else if (event.mouseButton.button == sf::Mouse::Right) {
                    for (size_t i = 0; i < points.size(); i++) {
                        if(abs(mousepos.x - points[i].x) < 10.f && abs(mousepos.y - points[i].y) < 10.f) {
                            points.erase(points.begin() + i);
                            break;
                        }
                    }
                }
            }
            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::R) {
                    points.clear();
                }
            }

        }

        // reset window

        window.display();
        
    }

    return 0;
}