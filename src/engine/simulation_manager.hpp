#pragma once

#include "simulation.hpp"
#include "simulation_type.hpp"

#include <memory>

class SimulationManager
{
public:
    explicit SimulationManager(SimulationType initialSimulation);

    void setSimulation(SimulationType type);
    void reset();
    void update(float dt, const SimulationState& state);

    const std::vector<Particle>& getParticles() const;

private:
    static std::unique_ptr<Simulation> createSimulation(SimulationType type);

    SimulationType m_activeType;
    std::unique_ptr<Simulation> m_activeSimulation;
};
