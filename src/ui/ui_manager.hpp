#pragma once

#include "imgui-SFML.h"
#include "imgui.h"
#include "simulation_state.h"
#include <SFML/Graphics.hpp>

class UIManager
{
public:
    void init(sf::RenderWindow &window);
    void handleEvent(const sf::Window &window, const sf::Event &event);
    void update(sf::RenderWindow &window, sf::Time dt, SimulationState &state);
    void render(sf::RenderWindow &window);
};