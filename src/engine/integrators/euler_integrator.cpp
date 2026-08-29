#include "euler_integrator.hpp"
#include "../particle.hpp"

void EulerIntegrator::integrate(Particle& particle, float dt)
{

    particle.velocity += particle.acceleration * dt;

    particle.position += particle.velocity * dt;
}