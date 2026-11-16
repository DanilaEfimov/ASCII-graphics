#pragma once

#include "bubble.hpp"
#include "cell.hpp"
#include <SFML/Graphics/ConvexShape.hpp>


struct State {
    sf::ConvexShape shape;
    sf::Vector2f velocity;
    double presure;
};

class Physics {

Cell& cell;
Bubble& bubble;

State state;

public:
    Physics(Cell& c, Bubble& b) : cell(c), bubble(b) {
        //TODO: initial state
    }

    const State& evolute() {
        //TODO: implement
        return this->state;
    }

};
