#pragma once

#include <vector>

class Particle;

class Integrator
{
public:
    virtual ~Integrator() = default;

    virtual void integrate(Particle& particle, float dt) = 0;
};