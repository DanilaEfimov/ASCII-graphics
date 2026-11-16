#pragma once

#include "coord_traits.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>

class Bubble {

using pos_t = coord_t<CoordCategory::UnsignedInteger>;
using vector_t = sf::Vector2f;

sf::CircleShape circle;

public:
    Bubble(std::size_t radius, vector_t pos)
        : circle(radius) {
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

};
