#include "gravitational_simulation.hpp"
#include "../utils/random.hpp"

#include <iostream>
#include <cmath>


constexpr int LIMIT_FRAME = 60;
constexpr float WINDOW_WIDTH = 800.f;
constexpr float WINDOW_HEIGHT = 600.f;



GravitationalSimulation::GravitationalSimulation(int particle_count, float radius, float mass, float gravitationalConstant)
    : m_G(gravitationalConstant)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    for (int i = 0; i < particle_count; i++)
    {
        Particle particle(radius, mass);

        particle.position.x = getRandomRange(
            particle.radius,
            WINDOW_WIDTH - particle.radius,
            gen);
        particle.position.y = getRandomRange(
            particle.radius,
            WINDOW_HEIGHT - particle.radius,
            gen);
        particle.velocity.x = getRandomRange(-100.f, 100.f, gen);
        particle.velocity.y = getRandomRange(-100.f, 100.f, gen);
        this->m_particles.push_back(std::move(particle));
    }
        for (auto& particle : m_particles)
    {
        particle.acceleration.x = 0.0f;
        particle.acceleration.y = 0.0f;
    }
}

void GravitationalSimulation::update(float dt, const SimulationState &state)
{
    calculateAccelerations();

    for (auto& particle : m_particles)
    {
        particle.update(dt * state.timeScale, WINDOW_WIDTH, WINDOW_HEIGHT);
    }
}

void GravitationalSimulation::calculateAccelerations()
{
    for (std::size_t i = 0; i < m_particles.size(); ++i)
    {
        Vec2<float> acceleration(0.0f, 0.0f);

        const auto positionI = m_particles[i].position;

        for (std::size_t j = 0; j < m_particles.size(); ++j)
        {
            if (i == j)
                continue;

            const auto positionJ = m_particles[j].position;

            const Vec2<float> direction =
                positionJ - positionI;

            const float distanceSquared =
                direction.x * direction.x +
                direction.y * direction.y;
            
            if (distanceSquared < 25.0f)
                continue;

            const float distance =
                std::sqrt(distanceSquared);

            const float inverseDistance =
                1.0f / distance;

            const Vec2<float> directionNormalized =
                direction * inverseDistance;

            const float accelerationMagnitude =
                m_G *
                m_particles[j].mass /
                distanceSquared;

            acceleration +=
                directionNormalized * accelerationMagnitude;
        }

        m_particles[i].acceleration.x = acceleration.x;
        m_particles[i].acceleration.y = acceleration.y;
    }
}

const std::vector<Particle>&
GravitationalSimulation::getParticles() const
{
    return m_particles;
}