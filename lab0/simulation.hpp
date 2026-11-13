#pragma once

#include "context.hpp"
#include <algorithm>

class Simulation {
    SimulationContext context;

public:
    const SimulationContext& getContext() const noexcept {
        return this->context;
    }

    SimulationContext& getContext() {
        return this->context;
    }

    void step(std::size_t worldWidth) {
        auto& ctx = this->context;
        if (!ctx.isRunning()) return;

        const auto pos = ctx.getPosition();
        const auto dir = ctx.getDirection();

        if (dir == Direction::LeftToRight) {
            ctx.setPosition(std::min(pos + 1, worldWidth));
        } else {
            ctx.setPosition(pos > 0 ? pos - 1 : 0);
        }
    }

};
