#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

// screen settings
int screenx = 1920;
int screeny = 1080;

// storage for the curve currently being drawn
vector<sf::Vector2f> tempcurve = {};

// storage for all finished curves
vector<vector<sf::Vector2f>> curves = {};

// math for smooth lines
sf::Vector2f lerp(sf::Vector2f a, sf::Vector2f b, float t) {
    return a + t * (b - a);
}

// recursive math to find bezier point
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

        // draw all the permanent saved curves
        for (const auto& saved_points : curves) {
            if (saved_points.size() >= 2) {
                sf::VertexArray saved_va(sf::LineStrip);
                for (float t = 0.f; t <= 1.f; t += 0.01f) {
                    sf::Vector2f cp = getBezierPoint(saved_points, t);
                    saved_va.append(sf::Vertex(cp, sf::Color(100, 100, 100))); // grey for saved
                }
                window.draw(saved_va);
            }
        }

        // draw helper lines for the active curve
        sf::VertexArray line(sf::LineStrip, tempcurve.size());
        for (size_t i = 0; i < tempcurve.size(); i++)
        {
            line[i].position = tempcurve[i];
            line[i].color = sf::Color(200, 200, 200);
        }
        window.draw(line);

        // draw the active bezier curve in red
        if (tempcurve.size() >= 2) {
            sf::VertexArray curve_va(sf::LineStrip);
            for (float t = 0.f; t <= 1.f; t += 0.01f) {
                sf::Vector2f cp = getBezierPoint(tempcurve, t);
                curve_va.append(sf::Vertex(cp, sf::Color::Red));
            }
            window.draw(curve_va);
        }   

        // draw the control points for the active curve
        for (size_t i = 0; i < tempcurve.size(); i++)
        {
            sf::CircleShape point(10.f);
            point.setFillColor(sf::Color::Black);
            point.setOrigin(10.f, 10.f);
            point.setPosition(tempcurve[i]);
            window.draw(point);
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::MouseButtonPressed) {
                // left click to add points to active curve
                if(event.mouseButton.button == sf::Mouse::Left) {
                    tempcurve.push_back(mousepos);
                }
                // right click to delete points from active curve
                else if (event.mouseButton.button == sf::Mouse::Right) {
                    for (size_t i = 0; i < tempcurve.size(); i++) {
                        if(abs(mousepos.x - tempcurve[i].x) < 10.f && abs(mousepos.y - tempcurve[i].y) < 10.f) {
                            tempcurve.erase(tempcurve.begin() + i);
                            break;
                        }
                    }
                }
            }

            if(event.type == sf::Event::KeyPressed) {
                // enter to save active curve and start a new one
                if (event.key.code == sf::Keyboard::Enter) {
                    if (!tempcurve.empty()) {
                        curves.push_back(tempcurve);
                        tempcurve.clear();
                    }
                }
                // delete key to wipe the current active curve
                if(event.key.code == sf::Keyboard::Delete) {
                    tempcurve.clear();
                }
                // r key to wipe everything
                if(event.key.code == sf::Keyboard::R) {
                    tempcurve.clear();
                    curves.clear();
                }
            }
        }

        window.display();
    }

    return 0;
}