#include "Random/random.hpp"

namespace Random
{
    static uint32_t g_seed = 1;

    void srand(uint32_t seed) noexcept
    {
        g_seed = seed;
    }

    uint32_t rand() noexcept
    {
        g_seed = g_seed * 1664525UL + 1013904223UL;
        return g_seed;
    }

    uint32_t random(uint32_t min, uint32_t max) noexcept
    {
        return min + (rand() % (max - min));
    }
}
