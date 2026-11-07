#include <SFML/Graphics.hpp>

#include "simulation_state.h"
#include "ui/ui_manager.hpp"
#include "engine/simulation_manager.hpp"
#include "render/renderer.hpp"
#include "statistics_manager.hpp"


constexpr int LIMIT_FRAME = 60;
constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;
constexpr int PARTICLE_COUNT = 1000;
constexpr float PARTICLE_RADIUS = 5.f;
constexpr float PARTICLE_MASS = 1.f;

int main()
{
    sf::Clock clock;
    ParticleRenderer ParticleRenderer(PARTICLE_COUNT, PARTICLE_RADIUS);
    SimulationState state;
    StatisticsManager statistics_manager;
    UIManager uiManager;
    SimulationType selectedSimulation = SimulationType::Gravitational;
    SimulationManager simulationManager(selectedSimulation);

    sf::RenderWindow window = initializeWindowRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, LIMIT_FRAME);
    uiManager.init(window);

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
        const bool resetRequested = uiManager.update(
            window, dt, state, selectedSimulation);
        simulationManager.setSimulation(selectedSimulation);
        if (resetRequested)
            simulationManager.reset();
        simulationManager.update(dt.asSeconds(), state);

        // Render
        window.clear();
        uiManager.render(window);
        ParticleRenderer.render(window, simulationManager.getParticles());
        window.display();

        // Usage resources statistics
        statistics_manager.update(
            state,
            static_cast<float>(dt.asSeconds()),
            static_cast<int>(simulationManager.getParticles().size()),
            0);
    }
    ImGui::SFML::Shutdown();

    return 0;
}