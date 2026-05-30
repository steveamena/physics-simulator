#pragma once

#include <SFML/Graphics.hpp>

class Particle {
public:
    Particle(float radius);

    void update(float dt);
    void render(sf::RenderWindow& window) const;
    void syncGraphics();

    sf::Vector2f position;
    sf::Vector2f velocity;

    float radius;
    float mass;

private:
    sf::CircleShape shape;
};