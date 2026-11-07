#include "gravitational_simulation.hpp"
#include <cmath>


constexpr int LIMIT_FRAME = 60;
constexpr float WINDOW_WIDTH = 800.f;
constexpr float WINDOW_HEIGHT = 600.f;
constexpr float PI = 3.14159265359f;
constexpr float CENTRAL_MASS_MULTIPLIER = 100.f;
constexpr float MIN_ORBIT_RADIUS = 80.f;
constexpr float ORBIT_RADIUS_STEP = 8.f;



GravitationalSimulation::GravitationalSimulation(int particle_count, float radius, float mass)
    : m_particle_count(particle_count), m_radius(radius), m_mass(mass)
{
    reset();
}

void GravitationalSimulation::reset()
{
    m_particles.clear();

    const int particle_count = m_particle_count;
    if (particle_count <= 0)
        return;

    const Vec2<float> center(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f);

    Particle centralParticle(m_radius * 2.5f, m_mass * CENTRAL_MASS_MULTIPLIER);
    centralParticle.position = center;
    centralParticle.velocity = {0.0f, 0.0f};
    m_particles.push_back(centralParticle);

    const int satelliteCount = particle_count - 1;
    const int ringCount = static_cast<int>(std::ceil(std::sqrt(
        static_cast<float>(satelliteCount))));
    for (int i = 0; i < satelliteCount; ++i)
    {
        Particle particle(m_radius, m_mass);
        const int ring = i % ringCount;
        const int particleInRing = i / ringCount;
        const int particlesInRing =
            (satelliteCount + ringCount - 1 - ring) / ringCount;
        const float orbitRadius = MIN_ORBIT_RADIUS +
                                   ORBIT_RADIUS_STEP * static_cast<float>(ring);
        const float angle = 2.0f * PI * static_cast<float>(particleInRing) /
                            static_cast<float>(particlesInRing);

        particle.position = {
            center.x + orbitRadius * std::cos(angle),
            center.y + orbitRadius * std::sin(angle)};

        const float orbitalSpeed = std::sqrt(
            500.0f * centralParticle.mass / orbitRadius);
        particle.velocity = {
            -orbitalSpeed * std::sin(angle),
            orbitalSpeed * std::cos(angle)};

        m_particles.push_back(particle);
    }
        for (auto& particle : m_particles)
    {
        particle.acceleration.x = 0.0f;
        particle.acceleration.y = 0.0f;
    }
}

void GravitationalSimulation::update(float dt, const SimulationState &state)
{
    if (state.paused)
        return;

    calculateAccelerations(state.gravitationalConstant);

    for (auto& particle : m_particles)
    {
        particle.update(dt * state.timeScale, WINDOW_WIDTH, WINDOW_HEIGHT);
    }
}

void GravitationalSimulation::calculateAccelerations(float G)
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
                G * m_particles[j].mass / distanceSquared;

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