#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <iomanip>

constexpr float PI = 3.14159265358979323846f;

sf::Vector2f rotatePoint(const sf::Vector2f& point,
                         const sf::Vector2f& center,
                         float angleRadians) {
    const float dx = point.x - center.x;
    const float dy = point.y - center.y;
    const float c = std::cos(angleRadians);
    const float s = std::sin(angleRadians);

    return {
        center.x + dx * c - dy * s,
        center.y + dx * s + dy * c
    };
}

int main() {
    float x1, y1, x2, y2, cx, cy, angularSpeed;

    std::cout << "Rotation of a segment around a fixed point\n";
    std::cout << "Enter the first endpoint (x1 y1): ";
    if (!(std::cin >> x1 >> y1)) return 1;
    std::cout << "Enter the second endpoint (x2 y2): ";
    if (!(std::cin >> x2 >> y2)) return 1;
    std::cout << "Enter the rotation center (cx cy): ";
    if (!(std::cin >> cx >> cy)) return 1;
    std::cout << "Enter angular speed in degrees per second: ";
    if (!(std::cin >> angularSpeed)) return 1;

    const sf::Vector2f initialA{x1, y1};
    const sf::Vector2f initialB{x2, y2};
    const sf::Vector2f center{cx, cy};
    const float speedRadians = angularSpeed * PI / 180.0f;

    sf::RenderWindow window(sf::VideoMode(1000, 700), "Lab 2 - Segment rotation");
    window.setFramerateLimit(60);

    sf::Clock clock;
    float angle = 0.0f;

    sf::CircleShape centerMarker(5.0f);
    centerMarker.setOrigin(5.0f, 5.0f);
    centerMarker.setFillColor(sf::Color::Red);
    centerMarker.setPosition(center);

    sf::CircleShape endpointA(4.0f);
    endpointA.setOrigin(4.0f, 4.0f);
    endpointA.setFillColor(sf::Color::Cyan);
    sf::CircleShape endpointB(4.0f);
    endpointB.setOrigin(4.0f, 4.0f);
    endpointB.setFillColor(sf::Color::Yellow);

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
        }

        const float dt = clock.restart().asSeconds();
        angle += speedRadians * dt;

        const sf::Vector2f a = rotatePoint(initialA, center, angle);
        const sf::Vector2f b = rotatePoint(initialB, center, angle);

        sf::Vertex line[] = {
            sf::Vertex(a, sf::Color::Cyan),
            sf::Vertex(b, sf::Color::Yellow)
        };

        endpointA.setPosition(a);
        endpointB.setPosition(b);

        window.clear(sf::Color(24, 27, 34));
        window.draw(line, 2, sf::Lines);
        window.draw(centerMarker);
        window.draw(endpointA);
        window.draw(endpointB);
        window.display();
    }

    return 0;
}
