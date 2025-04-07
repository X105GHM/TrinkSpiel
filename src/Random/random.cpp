#include "Random/random.hpp"
#include "Hardware/hardware.hpp"
#include <util/delay.h>

namespace Random
{
    static uint32_t g_state = 0;

    static uint32_t generateEntropy()
    {
        uint32_t seed = 0;
        for (int i = 0; i < 8; i++)
        {
            Hardware::delay(5);
            uint16_t adcValue = Hardware::readADC(Hardware::PIN_ADC);
            seed ^= adcValue; 
            seed = (seed << 3) | (seed >> (32 - 3));
        }
        return seed;
    }

    void init() noexcept
    {
        g_state = generateEntropy();
        if (g_state == 0)
        {
            g_state = 0xACE1u;
        }
    }

    uint32_t next() noexcept
    {
        uint32_t x = g_state;
        x ^= x << 13;
        x ^= x >> 17;
        x ^= x << 5;
        g_state = x;
        return x;
    }

    uint32_t random(uint32_t min, uint32_t max) noexcept
    {
        return min + (next() % (max - min));
    }
}
