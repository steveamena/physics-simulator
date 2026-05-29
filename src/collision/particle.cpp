#include "Particle.hpp"

Particle::Particle(float radius)
{
    this->radius = radius;
    mass = 1.f;

    shape.setRadius(radius);
    shape.setFillColor(sf::Color::Cyan);
}

void Particle::syncGraphics()
{
    shape.setPosition({
        position.x - radius,
        position.y - radius
    });
}

void Particle::update(float dt)
{
    position += velocity * dt;
}

void Particle::render(sf::RenderWindow& window) const
{
    window.draw(shape);
}