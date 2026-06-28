#pragma once

struct SimulationState
{
    float gravity = 500.0f;
    float timeScale = 1.0f;
    float fps = 0;
    bool paused = false;
};