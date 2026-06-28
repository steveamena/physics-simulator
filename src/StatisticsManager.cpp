#include "StatisticsManager.hpp"
#include <windows.h>
#include <psapi.h>

void StatisticsManager::update(float dt,
                               int particleCount,
                               int collisionCount)
{
    simulationState.frameTimeMs = dt * 1000.0f;
    simulationState.fps = 1.0f / dt;

    simulationState.particleCount = particleCount;
    simulationState.collisionCount = collisionCount;

    simulationState.memoryUsageMB = getMemoryUsageMB();
    simulationState.cpuUsage = 0.f;
}

float StatisticsManager::getMemoryUsageMB()
{
    PROCESS_MEMORY_COUNTERS_EX pmc;

    if (GetProcessMemoryInfo(
            GetCurrentProcess(),
            reinterpret_cast<PROCESS_MEMORY_COUNTERS*>(&pmc),
            sizeof(pmc)))
    {
        return static_cast<float>(pmc.WorkingSetSize) / (1024.0f * 1024.0f);
    }

    return 0.0f;
}