#pragma once

#include "particle.hpp"
#include "simulation_state.h"

#include <vector>

class Simulation
{
public:
    virtual ~Simulation() = default;

    virtual void reset() = 0;
    virtual void update(float dt, const SimulationState& state) = 0;
    virtual const std::vector<Particle>& getParticles() const = 0;
};
