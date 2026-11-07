#include "../particle.hpp"
#include "../simulation.hpp"
#include "simulation_state.h"


#include <vector>


class GravitationalSimulation : public Simulation
{
public:
    GravitationalSimulation(int particle_count, float radius, float mass);

    void addParticle(const Particle& particle);
    void reset() override;

    void update(float dt, const SimulationState &state) override;

    const std::vector<Particle>& getParticles() const override;

private:
    int m_particle_count;
    float m_radius;
    float m_mass;
    void calculateAccelerations(float G);

private:
    std::vector<Particle> m_particles;

    float m_G;
};