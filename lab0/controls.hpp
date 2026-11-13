#pragma once

#include "simulation.hpp"
#include <algorithm>

struct KeyMap {
    const char direction_ltr = 'd';
    const char direction_rtl = 'a';
    const char speed_up = '+';
    const char speed_down = '-';
    const char pause = 'p';
};

class Controler {
    Simulation& simulation;
    KeyMap keys;

public:
    Controler(KeyMap km, Simulation& sim) : keys(km), simulation(sim) {}

    void process(char signal) {
        auto& context = this->simulation.getContext();
        auto speed = context.getSpeed();
        bool running = context.isRunning();

        if (signal == keys.direction_rtl) {
            context.setDirection(Direction::RightToLeft);
        }
        else if (signal == keys.direction_ltr) {
            context.setDirection(Direction::LeftToRight);
        }
        else if (signal == keys.speed_up) {
            // overflowing bound
            context.setSpeed(std::max(speed, static_cast<SimulationContext::speed_t>(speed+1)));
        }
        else if (signal == keys.speed_down) {
            // underflowing bound
            context.setSpeed(std::min(speed, static_cast<SimulationContext::speed_t>(speed-1)));
        }
        else if (signal == keys.pause) {
            if(running) context.pause();
            else context.resume();
        }
    }

    const KeyMap& getKeymap() const noexcept {
        return this->keys;
    }
};
