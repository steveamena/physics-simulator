#include <iostream>
#include <string.h>
#include "ui_manager.hpp"

void UIManager::init(sf::RenderWindow &window)
{
    static_cast<void>(ImGui::SFML::Init(window));
}

void UIManager::handleEvent(const sf::Window &window, const sf::Event &event)
{
    ImGui::SFML::ProcessEvent(window, event);
}

void UIManager::update(sf::RenderWindow &window, sf::Time dt, SimulationState &state)
{
    ImGui::SFML::Update(window, dt);

    ImGui::Begin("Collision Controls");

    ImGui::Text("Play with the sliders");

    ImGui::SliderFloat("Gravitational Constant", &state.gravitationalConstant, 0.0f, 1000.0f);

    ImGui::SliderFloat("Time Scale", &state.timeScale, 0.0f, 2.0f);

    ImGui::Text("FPS: %.1f", state.fps);

    if (ImGui::Button(state.paused ? "Resume" : "Pause"))
        state.paused = !state.paused;

    if (ImGui::Button("Reset"))
    {
        // will be wired later
    }

    ImGui::Text("Frame Time: %.2f ms", state.frameTimeMs);

    ImGui::Separator();

    ImGui::Text("Particles: %d", state.particleCount);

    ImGui::Text("Collisions: %d", state.collisionCount);

    ImGui::Separator();

    ImGui::Text("Memory: %.2f MB", state.memoryUsageMB);

    ImGui::Text("CPU: %.1f %%", state.cpuUsage);

    ImGui::End();
}

void UIManager::render(sf::RenderWindow &window)
{
    ImGui::SFML::Render(window);
}
