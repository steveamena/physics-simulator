#include "renderer.hpp"

ParticleRenderer::ParticleRenderer(int totalParticles, float radius)
{

    for (int i = 0; i < totalParticles; i++)
    {
        sf::CircleShape shape;
        shape.setFillColor(sf::Color::Cyan);
        shape.setRadius(radius);
        shapes.push_back(shape);
    }
}
void ParticleRenderer::syncGraphics(const Particles &particles)
{
    for (std::size_t i = 0; i < particles.size(); ++i)
    {
        const auto &particle = particles[i];
        auto &shape = shapes[i];

        shape.setPosition(
            {particle.position.x - particle.radius,
             particle.position.y - particle.radius});
    }
}

void ParticleRenderer::render(sf::RenderWindow &window, const Particles &particles)
{
    syncGraphics(particles);
    for (const auto &shape : shapes)
    {
        window.draw(shape);
    }
}

sf::RenderWindow initializeWindowRenderer(int window_width, int window_height, int limit_frame)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(
                                {static_cast<int>(window_width),
                                 static_cast<int>(window_height)}),
                            "SFML window");
    window.setFramerateLimit(limit_frame);
    return window;
}