#pragma once


#include "integrator.hpp"

class EulerIntegrator : public Integrator
{
public:
    void integrate(Particle& particle, float dt) override;
};