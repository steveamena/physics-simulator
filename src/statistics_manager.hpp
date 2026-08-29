#include "simulation_state.h"
#include <chrono>
#include <windows.h>
#include <psapi.h>
#include <iostream>

class StatisticsManager
{
public:
    StatisticsManager();
    void update(SimulationState& simulation_state, float dt,
                int particleCount,
                int collisionCount);


private:
    SimulationState simulation_state;
    HANDLE process_;

    // FPS variables
    int frame_count_ = 0;
    std::chrono::steady_clock::time_point last_fps_update_;

    //CPU usage metrics
    std::chrono::steady_clock::time_point last_cpu_update_;
    int last_cpu_time_ = 0;
    
    // Methods
    float get_memory_usage_mb();
    float get_fps(float fps);
    float get_cpu_usage(float cpu_usage);
};