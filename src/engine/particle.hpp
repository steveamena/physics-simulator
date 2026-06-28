#pragma once

#include "vector.hpp"

class Particle
{
public:
    Particle(float radius, float mass);
    void update(float dt);

    Vec2<float> position;
    Vec2<float> velocity;

    float radius;
    float mass;
};