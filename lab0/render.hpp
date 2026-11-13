#pragma once

#include "simulation.hpp"
#include "controls.hpp"
#include "utils.hpp"
#include <iostream>
#include <string>
#include <stdexcept>

struct WindowSize {
    std::size_t width;
    std::size_t height;
};

class Renderer {

WindowSize window_size;
const Simulation& simulation;

    bool isValidWindowSize() const noexcept {
        return this->window_size.width != 0
                && this->window_size.height != 0;
    }

public:
    Renderer(const Simulation& sim, WindowSize ws)
        : simulation(sim), window_size(ws) {}

    void draw() {
        const auto& context = this->simulation.getContext();
        if(!context.isRunning()) return;

        this->window_size = current_window_size();
        if(!this->isValidWindowSize())
            throw std::runtime_error("Renderer: invalid window size");

        const std::size_t pos = context.getPosition();
        if(pos >= window_size.width) return;

        std::string line(window_size.width, ' ');
        line[pos] = context.getCharacter();

        std::cout << '\r' << line << std::flush;
    }

    void onResizeWindow(WindowSize newWindowSize) {
        this->window_size = newWindowSize;
    }

};
