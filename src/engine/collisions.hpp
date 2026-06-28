#include <random>
#include <tuple>
#include <vector>

#include "particle.hpp"
#include "SimulationState.h"

using CollisionPairs = std::vector<std::tuple<size_t, size_t>>;
using Particles = std::vector<Particle>;

class Collisions
{
public:
    Collisions(int particle_count, float radius, float mass);
    void update(float dt, const SimulationState &state);
    Particles getParticles();

private:
    Particles particles;
    CollisionPairs detectCollisions(const Particles &particles);
    void calculateVelocitiesAndResolveOverlap(Particles &particles, const CollisionPairs &collisionPairs);
    float getRandomRange(float start, float end, std::mt19937 &gen);
};