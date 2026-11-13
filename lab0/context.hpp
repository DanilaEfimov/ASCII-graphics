#pragma once

#include <cstdint>

enum class Direction  : uint8_t {
    RightToLeft,
    LeftToRight,
};


class SimulationContext {
    Direction direction;
    char character;
    bool running = true;

public:
    SimulationContext(Direction direction, char ch)
        : direction(direction), character(ch) {}

    Direction getDirection() const noexcept {
        return this->direction;    
    }

    void setDirection(Direction newDirection) {
        this->direction = newDirection;
    }

    char getCharacter() const noexcept {
        return this->character;
    }

    void setCharacter(char newCharacter) {
        this->character = newCharacter;
    }

    void pause() {
        this->running = false;
    }

    void resume() {
        this->running = true;
    }
};
