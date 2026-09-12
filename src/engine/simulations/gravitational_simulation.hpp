#include "../particle.hpp"
#include "simulation_state.h"


#include <vector>


class GravitationalSimulation
{
public:
    GravitationalSimulation(int particle_count, float radius, float mass);

    void addParticle(const Particle& particle);

    void update(float dt, const SimulationState &state);

    const std::vector<Particle>& getParticles() const;

private:
    void calculateAccelerations(float G);

private:
    std::vector<Particle> m_particles;

    float m_G;
};