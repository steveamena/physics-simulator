#include <SFML/Graphics.hpp>
#include "engine/particle.hpp"
#include <vector>

using Particles = std::vector<Particle>;

class ParticleRenderer
{
public:
    ParticleRenderer(int totalParticles, float radius);
    void render(sf::RenderWindow &window, const Particles &particles);

private:
    void syncGraphics(const Particles &particle);
    std::vector<sf::CircleShape> shapes;
};

sf::RenderWindow initializeWindowRenderer(int window_width, int window_height, int limit_frame);
