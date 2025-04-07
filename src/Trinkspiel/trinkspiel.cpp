#include "Trinkspiel/trinkspiel.hpp"
#include "Hardware/hardware.hpp"
#include "Random/random.hpp"

namespace Trinkspiel
{

    void run() noexcept
    {
        Hardware::delay(50);

        uint8_t startLED = Random::random(0, 6);

        uint32_t baseCycles = 50;
        uint32_t extraCycles = Random::random(0, 10);
        uint32_t totalCycles = baseCycles + extraCycles;

        uint32_t delayTime = 10;
        uint8_t currentLED = startLED;

        for (uint32_t i = 0; i < totalCycles; i++)
        {
            currentLED = (startLED + i) % 6;
            Hardware::setMuxChannel(currentLED);
            Hardware::delay(delayTime);
            delayTime += 1;
        }

        for (uint8_t i = 0; i < 3; i++)
        {
            Hardware::setMuxChannel(currentLED);
            Hardware::delay(100);
            Hardware::setMuxChannel(6);
            Hardware::delay(100);
        }

        Hardware::setMuxChannel(currentLED);
        Hardware::delay(300);
        Hardware::setMuxChannel(7);
    }
}
