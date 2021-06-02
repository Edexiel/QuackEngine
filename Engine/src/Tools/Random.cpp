#include "Tools/Random.hpp"

#include <random>

int Random::Range(int start, int end)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(start, end);
    return distr(gen);
}

float Random::Range(float start, float end)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distr(start, end);
    return distr(gen);
}

int Random::RandomBool()
{
    return std::rand() % 2;
}
