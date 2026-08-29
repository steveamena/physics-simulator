#include "Particle.hpp"

Particle::Particle(float radius, float mass)
{
    this->radius = radius;
    this->mass = mass;
}

void Particle::update(float dt, float windows_width, float window_height)
{
    velocity += acceleration * dt;
    position += velocity * dt;
    if (position.x - radius < 0)
    {
        position.x = radius;
        velocity.x *= -1.0f;
    }
    else if (position.x + radius > windows_width)
    {
        position.x = windows_width - radius;
        velocity.x *= -1.0f;
        }

        if (position.y - radius < 0)
        {
            position.y = radius;
            velocity.y *= -1.0f;
        }
        else if (position.y + radius > window_height)
        {
            position.y = window_height - radius;
            velocity.y *= -1.0f;
        }
}