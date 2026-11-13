#pragma once

#include "render.hpp"
#include "listener.hpp"
#include "controls.hpp"
#include "simulation.hpp"
#include "utils.hpp"
#include <chrono>
#include <thread>

using namespace std::chrono;

class Engine {
    static constexpr auto time_unit = milliseconds(1000);

    Simulation& simulation;
    Renderer renderer;
    Listener listener;
    Controler& controler;

public:
    Engine(Simulation& sim, Controler& ctrl)
        : simulation(sim),
          renderer(sim, current_window_size()),
          listener(),
          controler(ctrl) {}

    void run() {
    using clock = std::chrono::steady_clock;
    auto last = clock::now();

    while (simulation.getContext().isRunning()) {
        while (auto key = listener.poll()) {
            controler.process(key.value());
        }

        const auto speed = simulation.getContext().getSpeed();
        const auto tick = std::chrono::milliseconds(1024 / speed);
        const auto now = clock::now();

        if (now - last >= tick) {
            simulation.step(current_window_size().width);
            renderer.draw();
            last = now;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    }
};
