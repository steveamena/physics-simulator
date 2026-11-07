#pragma once

#include "imgui-SFML.h"
#include "imgui.h"
#include "engine/simulation_type.hpp"
#include "simulation_state.h"
#include <SFML/Graphics.hpp>

class UIManager
{
public:
    void init(sf::RenderWindow &window);
    void handleEvent(const sf::Window &window, const sf::Event &event);
    bool update(sf::RenderWindow &window, sf::Time dt, SimulationState &state,
                SimulationType& selectedSimulation);
    void render(sf::RenderWindow &window);
};