#include <random>
#include <tuple>
#include <vector>

#include "particle.hpp"
#include "simulation.hpp"
#include "simulation_state.h"

using CollisionPairs = std::vector<std::tuple<size_t, size_t>>;
using Particles = std::vector<Particle>;

class Collisions : public Simulation
{
public:
    Collisions(int particle_count, float radius, float mass);
    void reset() override;
    void update(float dt, const SimulationState &state) override;
    const Particles& getParticles() const override;

private:
    int particle_count;
    float radius;
    float mass;
    Particles particles;
    CollisionPairs detectCollisions(const Particles &particles);
    void calculateVelocitiesAndResolveOverlap(Particles &particles, const CollisionPairs &collisionPairs);
    float getRandomRange(float start, float end, std::mt19937 &gen);
};