#pragma once

#include "vector.hpp"

class Particle
{
public:
    Particle(float radius, float mass);
    void update(float dt, float windows_width, float window_height);

    Vec2<float> position;
    Vec2<float> velocity;
    Vec2<float> acceleration;

    float radius;
    float mass;
};