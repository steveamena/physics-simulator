#include "Particle.hpp"

Particle::Particle(float radius, float mass):
    radius(radius), mass(mass){}

void Particle::update(float dt, float window_width, float window_height)
{
    m_integrator.integrate(*this, dt);
    constrain_to_bounds(window_width, window_height);
}

void Particle::constrain_to_bounds(float width, float height){
        if (position.x - radius < 0)
    {
        position.x = radius;
        velocity.x *= -1.0f;
    }
    else if (position.x + radius > width)
    {
        position.x = width - radius;
        velocity.x *= -1.0f;
        }

        if (position.y - radius < 0)
        {
            position.y = radius;
            velocity.y *= -1.0f;
        }
        else if (position.y + radius > height)
        {
            position.y = height - radius;
            velocity.y *= -1.0f;
        }
}