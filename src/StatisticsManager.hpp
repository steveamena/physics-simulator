#include "SimulationState.h"

class StatisticsManager
{
public:

    void update(float dt,
                int particleCount,
                int collisionCount);

    const SimulationState& getSimulationState() const;

private:
    SimulationState simulationState;
    float getMemoryUsageMB();
};