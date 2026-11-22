#pragma once

#include "coord_traits.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <algorithm>
#include <cstddef>

class Bubble {

using pos_t = coord_t<CoordCategory::UnsignedInteger>;
using vector_t = sf::Vector2f;

sf::CircleShape circle;

public:
    static constexpr float min_radius = 1.f;

    // pos -- левый верхний угол описывающего квадрата (как в sf::CircleShape)
    Bubble(std::size_t radius, vector_t pos)
        : circle(static_cast<float>(radius)) {
            this->circle.setPosition(pos);
        }

    void setColor(sf::Color c) {
        this->circle.setFillColor(c);
    }

    sf::Color getColor() const {
        return this->circle.getFillColor();
    }

    void setPosition(vector_t pos) {
        this->circle.setPosition(pos);
    }

    vector_t getPosition() const {
        return this->circle.getPosition();
    }

    void move(vector_t sh) {
        auto pos = this->circle.getPosition();
        this->circle.setPosition(pos + sh);
    }

    float getRadius() const {
        return this->circle.getRadius();
    }

    vector_t getCenter() const {
        float r = this->circle.getRadius();
        return this->circle.getPosition() + vector_t{r, r};
    }

    void setCenter(vector_t c) {
        float r = this->circle.getRadius();
        this->circle.setPosition(c - vector_t{r, r});
    }

    // Меняет радиус, сохраняя центр на месте
    void setRadius(float r) {
        auto c = this->getCenter();
        this->circle.setRadius(std::max(r, min_radius));
        this->setCenter(c);
    }

    void grow(float dr) {
        this->setRadius(this->getRadius() + dr);
    }

};
