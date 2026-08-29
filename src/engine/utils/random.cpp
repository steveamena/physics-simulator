#include "random.hpp"

float getRandomRange(float start, float end, std::mt19937 &gen)
{
    std::uniform_real_distribution<float> dist(start, end);
    return dist(gen);
}