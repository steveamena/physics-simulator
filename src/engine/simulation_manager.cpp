#include "simulation_manager.hpp"

#include "collisions.hpp"
#include "simulations/gravitational_simulation.hpp"

#include <stdexcept>

namespace
{
constexpr int PARTICLE_COUNT = 1000;
constexpr float PARTICLE_RADIUS = 5.0f;
constexpr float PARTICLE_MASS = 1.0f;
}

SimulationManager::SimulationManager(SimulationType initialSimulation)
    : m_activeType(initialSimulation),
      m_activeSimulation(createSimulation(initialSimulation))
{
}

void SimulationManager::setSimulation(SimulationType type)
{
    if (type == m_activeType)
        return;

    m_activeSimulation = createSimulation(type);
    m_activeType = type;
}

void SimulationManager::reset()
{
    m_activeSimulation->reset();
}

void SimulationManager::update(float dt, const SimulationState& state)
{
    m_activeSimulation->update(dt, state);
}

const std::vector<Particle>& SimulationManager::getParticles() const
{
    return m_activeSimulation->getParticles();
}

std::unique_ptr<Simulation> SimulationManager::createSimulation(SimulationType type)
{
    switch (type)
    {
    case SimulationType::Collisions:
        return std::make_unique<Collisions>(
            PARTICLE_COUNT, PARTICLE_RADIUS, PARTICLE_MASS);
    case SimulationType::Gravitational:
        return std::make_unique<GravitationalSimulation>(
            PARTICLE_COUNT, PARTICLE_RADIUS, PARTICLE_MASS);
    }

    throw std::invalid_argument("Unknown simulation type");
}
