#include <SFML/Graphics.hpp>

#include "SimulationState.h"
#include "ui/UIManager.hpp"
#include "collision/collisions.hpp"

constexpr int LIMIT_FRAME = 60;
constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

int main()
{

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(
                                {static_cast<int>(WINDOW_WIDTH),
                                 static_cast<int>(WINDOW_HEIGHT)}),
                            "SFML window");
    window.setFramerateLimit(LIMIT_FRAME);

    sf::Clock clock;

    SimulationState state;
    UIManager uiManager;
    Collisions collisions;

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
        collisions.render(window);
        window.display();

        // FPS statistics
        frameCount++;
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration<float>(currentTime - lastFPSUpdate);
        if (elapsed.count() >= 1.0f)
        {
            state.fps = static_cast<float>(frameCount) / elapsed.count();
            lastFPSUpdate = currentTime;
            frameCount = 0;
        }
    }
    ImGui::SFML::Shutdown();

    return 0;
}