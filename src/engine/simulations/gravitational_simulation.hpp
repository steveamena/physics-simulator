#include "../particle.hpp"
#include "simulation_state.h"


#include <vector>
#include <random>

class GravitationalSimulation
{
public:
    GravitationalSimulation(int particle_count, float radius, float mass, float gravitationalConstant);

    void addParticle(const Particle& particle);

    void update(float dt, const SimulationState &state);

    const std::vector<Particle>& getParticles() const;

private:
    void calculateAccelerations();

private:
    std::vector<Particle> m_particles;

    float m_G;
};