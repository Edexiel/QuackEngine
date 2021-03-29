#ifndef _RANDOM_
#define _RANDOM_

#include "Debug/Assertion.hpp"
#include <random>

class Random
{
public:

    inline static int RandomBool()
    {
        return std::rand() % 2;
    }

    inline static int Range(int start, int end)
    {
        return start + (std::rand() % (end - start + 1));
    }

    inline static float Range(float start, float end)
    {
        return start + (std::rand() % (unsigned int)((end - start + 1) * 100000) / 100000.f);
    }    
};

#endif