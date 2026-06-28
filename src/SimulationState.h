#pragma once

struct SimulationState
{
    float gravity = 500.0f;
    float timeScale = 1.0f;

    // Performance
    float fps = 0;
    float frameTimeMs = 0.0f;
    float cpuUsage = 0.0f;
    float memoryUsageMB = 0.0f;
    
    // Execution
    bool paused = false;

    // Simulation
    int particleCount = 0;
    int collisionCount = 0; 
};