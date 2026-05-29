#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include <tuple>
#include "particle.hpp"


using CollisionPairs = std::vector<std::tuple<size_t, size_t>>;
using Particles = std::vector<Particle>;

constexpr float GRAVITY = 98.f;
constexpr int LIMIT_FRAME = 60;
constexpr float WINDOW_WIDTH = 800.f;
constexpr float WINDOW_HEIGHT = 600.f;
constexpr int PARTICLE_COUNT = 50;

CollisionPairs detectCollisions(const Particles& particles){
    CollisionPairs collisions;
    for (size_t i = 0; i < particles.size(); i++){
        for (size_t j = i + 1; j < particles.size(); j++){
            const Particle& firstParticle = particles[i];
            const Particle& secondParticle = particles[j];
            float dx = firstParticle.position.x - secondParticle.position.x;
            float dy = firstParticle.position.y - secondParticle.position.y;

            float distanceSqr = dx * dx + dy * dy;
            float minDistance = firstParticle.radius + secondParticle.radius;
             if(distanceSqr < minDistance * minDistance){
                collisions.emplace_back(i, j);
            }
        }
    }
    return collisions;
}

void calculateVelocitiesAndResolveOverlap(Particles& particles, const CollisionPairs& collisionPairs)
{
    for (const auto& collisionPair : collisionPairs) {
        size_t i, j; 
        std::tie(i, j) = collisionPair;

        float diffX = particles[j].position.x - particles[i].position.x;
        float diffY = particles[j].position.y - particles[i].position.y;
        float d = std::sqrt(diffX * diffX + diffY * diffY);
        
        if(d <= 0.0001f) continue;

        // Solve particles overlaping
        float minDistance = particles[i].radius + particles[j].radius;
        float overlap = minDistance - d;
        float resolveX = (diffX / d) * (overlap * 0.5f);
        float resolveY = (diffY / d) * (overlap * 0.5f);

        // Separate the position of the particles        
        particles[i].position.x -= resolveX;
        particles[i].position.y -= resolveY;
        particles[j].position.x += resolveX;
        particles[j].position.y += resolveY;


        float n_x = diffX / d; 
        float n_y = diffY / d; 
        float p = 2 * (particles[i].velocity.x * n_x + particles[i].velocity.y * n_y - 
            particles[j].velocity.x * n_x - particles[j].velocity.y * n_y) / 
            (particles[i].mass + particles[j].mass); 
        particles[i].velocity.x -= p * particles[j].mass * n_x; 
        particles[i].velocity.y -= p * particles[j].mass * n_y; 
        particles[j].velocity.x += p * particles[i].mass * n_x; 
        particles[j].velocity.y += p * particles[i].mass * n_y;
    }
}

void updateParticlePosition(Particles& particles, float dt)
{
    // Apply forces (GRAVITY for now)
    for(auto& particle : particles){
        particle.position.x += particle.velocity.x * dt;
        particle.velocity.y += GRAVITY * dt;
        particle.position.y += particle.velocity.y * dt;
    
    // Wall collission
    if (particle.position.x - particle.radius < 0) {
        particle.position.x = particle.radius;
        particle.velocity.x *= -1.0f;
    } else if (particle.position.x + particle.radius > WINDOW_WIDTH) {
        particle.position.x = WINDOW_WIDTH - particle.radius;
        particle.velocity.x *= -1.0f;
    }

    if (particle.position.y - particle.radius < 0) {
        particle.position.y = particle.radius;
        particle.velocity.y *= -1.0f;
    } else if (particle.position.y + particle.radius > WINDOW_HEIGHT) {
        particle.position.y = WINDOW_HEIGHT - particle.radius;
        particle.velocity.y *= -1.0f;
        }
    }

    CollisionPairs collisionPairs = detectCollisions(particles);
    calculateVelocitiesAndResolveOverlap(particles, collisionPairs);

    for (auto& particle : particles) {
        particle.syncGraphics();
        }
}

float getRandomRange(float start, float end, std::mt19937& gen)
{
    std::uniform_real_distribution<float> dist(start, end);
    return dist(gen);
}


int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(
        {static_cast<int>(WINDOW_WIDTH), 
        static_cast<int>(WINDOW_HEIGHT)}), 
        "SFML window");
    window.setFramerateLimit(LIMIT_FRAME);
    
    // Create random distribution
    std::random_device rd;
    std::mt19937 gen(rd());

    Particles particles;
    for(int i = 0; i < PARTICLE_COUNT; i++) {
        Particle particle(10.f);

        particle.position.x = getRandomRange(
            particle.radius,
            WINDOW_WIDTH - particle.radius,
            gen
            );
        particle.position.y = getRandomRange(
            particle.radius,
            WINDOW_HEIGHT - particle.radius,
            gen
        );
        particle.velocity.x = getRandomRange(-100.f, 100.f, gen);
        particle.velocity.y = getRandomRange(-100.f, 100.f, gen);
        particle.syncGraphics();
        particles.push_back(std::move(particle));

    }
    // Start the game loop
    sf::Clock clock;
    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();
        updateParticlePosition(particles, dt);

        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
        }
 
        // Clear screen
        window.clear();
        
    for(const auto& particle : particles){
        particle.render(window);
    }
        // Update the window
        window.display();
    }
}