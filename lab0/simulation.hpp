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

};
