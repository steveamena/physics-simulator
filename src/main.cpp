#include <SFML/Graphics.hpp>

#include "SimulationState.h"
#include "ui/UIManager.hpp"
#include "engine/collisions.hpp"
#include "render/renderer.hpp"

constexpr int LIMIT_FRAME = 60;
constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;
constexpr int PARTICLE_COUNT = 30;
constexpr float PARTICLE_RADIUS = 5.f;
constexpr float PARTICLE_MASS = 1.f;

int main()
{
    sf::Clock clock;
    ParticleRenderer ParticleRenderer(PARTICLE_COUNT, PARTICLE_RADIUS);
    SimulationState state;
    UIManager uiManager;
    Collisions collisions(PARTICLE_COUNT, PARTICLE_RADIUS, PARTICLE_MASS);

    sf::RenderWindow window = initializeWindowRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, LIMIT_FRAME);
    uiManager.init(window);

    auto lastFPSUpdate = std::chrono::steady_clock::now();
    int frameCount = 0;

    // Start the game loop
    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            ImGui::SFML::ProcessEvent(window, *event);

            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        sf::Time dt = clock.restart();
        uiManager.update(window, dt, state);
        collisions.update(dt.asSeconds(), state);

        // Render
        window.clear();
        uiManager.render(window);
        ParticleRenderer.render(window, collisions.getParticles());
        window.display();

        // FPS statistics
        frameCount++;
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration<float>(currentTime - lastFPSUpdate);

        if (elapsed.count() >= 0.25f)
        {
            state.fps = static_cast<float>(frameCount) / elapsed.count();
            lastFPSUpdate = currentTime;
            frameCount = 0;
        }
    }
    ImGui::SFML::Shutdown();

    return 0;
}