#pragma once

#include "context.hpp"

class Simulation {
    SimulationContext context;

public:
    const SimulationContext& getContext() const noexcept {
        return this->context;
    }

    SimulationContext& getContext() {
        return this->context;
    }

    void step() {
        auto& ctx = this->context;
        if (!ctx.isRunning()) return;

        const auto pos = ctx.getPosition();
        const auto dir = ctx.getDirection();

        if (dir == Direction::LeftToRight) {
            ctx.setPosition(pos + 1);
        } else {
            ctx.setPosition(pos > 0 ? pos - 1 : 0);
        }
    }

};
