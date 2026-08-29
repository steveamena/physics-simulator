#include "statistics_manager.hpp"


StatisticsManager::StatisticsManager()
    : last_fps_update_(std::chrono::steady_clock::now()), last_cpu_update_(std::chrono::steady_clock::now()), process_(GetCurrentProcess()){}

void StatisticsManager::update(SimulationState& simulation_state, float dt,
                               int particleCount,
                               int collisionCount)
{
    simulation_state.frameTimeMs = dt * 1000.0f;
    simulation_state.fps = get_fps(simulation_state.fps);

    simulation_state.particleCount = particleCount;
    simulation_state.collisionCount = collisionCount;

    simulation_state.memoryUsageMB = get_memory_usage_mb();
    simulation_state.cpuUsage = get_cpu_usage(simulation_state.cpuUsage);
}

float StatisticsManager::get_memory_usage_mb()
{
    PROCESS_MEMORY_COUNTERS pmc;

    if (GetProcessMemoryInfo(
            GetCurrentProcess(), &pmc, sizeof(pmc)))
    {
        return static_cast<float>(pmc.WorkingSetSize) / (1024.0f * 1024.0f);
    }
    return 0.0f;
}

float StatisticsManager::get_fps(float previous_fps){
            // FPS statistics
        frame_count_++;
        auto currentTime = std::chrono::steady_clock::now();
        const float elapsed = std::chrono::duration<float>(currentTime - last_fps_update_).count();
        if (elapsed >= 0.25f)
        {
            float calculated_fps = static_cast<float>(frame_count_) / elapsed;
            last_fps_update_ = currentTime;
            frame_count_ = 0;
            return calculated_fps;
        }
        return previous_fps;
}

float StatisticsManager::get_cpu_usage(float cpu_usage)
{
    FILETIME creation_time;
    FILETIME exit_time;
    FILETIME kernel_time;
    FILETIME user_time;

    if (!GetProcessTimes(
            process_,
            &creation_time,
            &exit_time,
            &kernel_time,
            &user_time))
    {
        return cpu_usage;
    }

    const std::uint64_t kernel =
        (static_cast<std::uint64_t>(kernel_time.dwHighDateTime) << 32) |
        kernel_time.dwLowDateTime;

    const std::uint64_t user =
        (static_cast<std::uint64_t>(user_time.dwHighDateTime) << 32) |
        user_time.dwLowDateTime;

    const std::uint64_t current_cpu_time = kernel + user;

    const auto current_time = std::chrono::steady_clock::now();

    const float elapsed =
        std::chrono::duration<float>(
            current_time - last_cpu_update_
        ).count();

    // Update CPU usage every 250 ms
    if (elapsed >= 0.25f)
    {
        // First measurement
        if (last_cpu_time_ == 0)
        {
            last_cpu_time_ = current_cpu_time;
            last_cpu_update_ = current_time;

            return cpu_usage;
        }

        // FILETIME uses 100-nanosecond units.
        const float cpu_time =
            static_cast<float>(
                current_cpu_time - last_cpu_time_
            ) * 1.0e-7f;

        SYSTEM_INFO system_info;
        GetSystemInfo(&system_info);

        const float number_of_processors =
            static_cast<float>(
                system_info.dwNumberOfProcessors
            );

        cpu_usage =
            (cpu_time /
             (elapsed * number_of_processors))
            * 100.0f;

        last_cpu_time_ = current_cpu_time;
        last_cpu_update_ = current_time;
    }

    return cpu_usage;
}