#include "bubble.hpp"
#include "cell.hpp"
#include "physics.hpp"

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>
#include <format>
#include <optional>

namespace {

bool down(sf::Keyboard::Key a, sf::Keyboard::Key b) {
    return sf::Keyboard::isKeyPressed(a) || sf::Keyboard::isKeyPressed(b);
}

// Направление по WASD / стрелкам, длина <= 1 (по диагонали не быстрее)
sf::Vector2f readDirection() {
    using K = sf::Keyboard::Key;
    sf::Vector2f d{0.f, 0.f};
    if (down(K::Left, K::A))  d.x -= 1.f;
    if (down(K::Right, K::D)) d.x += 1.f;
    if (down(K::Up, K::W))    d.y -= 1.f;
    if (down(K::Down, K::S))  d.y += 1.f;

    const float len = std::hypot(d.x, d.y);
    return len > 0.f ? d / len : d;
}

} // namespace

int main() {
    constexpr unsigned width = 900;
    constexpr unsigned height = 700;
    constexpr unsigned margin = 60;

    constexpr float move_speed = 300.f;     // px/s
    constexpr float growth_rate = 140.f;    // px/s, пока зажат Space
    constexpr float title_period = 0.2f;    // как часто обновлять заголовок, с

    sf::RenderWindow window(sf::VideoMode({width, height}), "Sculptor");
    window.setFramerateLimit(60);

    Cell cell(sf::Vector2u{margin, margin},
              sf::Vector2u{width - 2 * margin, height - 2 * margin});
    const sf::FloatRect bounds = cell.getBounds();
    const float max_radius = std::hypot(bounds.size.x, bounds.size.y);

    Bubble bubble(40, {0.f, 0.f});
    bubble.setColor(sf::Color(90, 170, 255));
    bubble.setCenter(bounds.getCenter());

    Physics physics(cell, bubble);

    sf::RectangleShape frame(bounds.size);
    frame.setPosition(bounds.position);
    frame.setFillColor(sf::Color::Transparent);
    frame.setOutlineColor(sf::Color(220, 220, 230));
    frame.setOutlineThickness(2.f);

    sf::Clock clock;
    float title_timer = 0.f;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            } else if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                if (key->code == sf::Keyboard::Key::Escape)
                    window.close();
            } else if (const auto* resized = event->getIf<sf::Event::Resized>()) {
                // Вид 1:1 к пикселям, рамка по центру окна: без растяжения круг остаётся кругом
                window.setView(sf::View(bounds.getCenter(), sf::Vector2f(resized->size)));
            }
        }

        const float dt = std::min(clock.restart().asSeconds(), 0.05f);

        // Управление: WASD / стрелки -- двигать; Space -- расширять; Backspace -- сжимать
        physics.setVelocity(readDirection() * move_speed);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
            bubble.setRadius(std::min(bubble.getRadius() + growth_rate * dt, max_radius));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Backspace))
            bubble.grow(-growth_rate * dt);

        const State& state = physics.evolute(dt);

        title_timer += dt;
        if (title_timer >= title_period) {
            title_timer = 0.f;
            window.setTitle(std::format("Sculptor | r = {:.0f} | pressure = {:.2f}",
                                        bubble.getRadius(), state.presure));
        }

        window.clear(sf::Color(24, 24, 30));
        window.draw(state.shape);
        window.draw(frame);
        window.display();
    }

    return 0;
}
