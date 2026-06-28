#include "Particle.hpp"

Particle::Particle(float radius, float mass)
{
    this->radius = radius;
    this->mass = mass;
}

void Particle::update(float dt)
{
    position += velocity * dt;
}