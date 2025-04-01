#include "Trinkspiel/trinkspiel.hpp"
#include "Hardware/hardware.hpp"
#include "Random/random.hpp"

namespace Trinkspiel
{

    inline bool isButtonPressed() noexcept
    {
        return !Hardware::digitalRead(Hardware::PIN_BUTTON);
    }

    void run() noexcept
    {
        Hardware::setMuxChannel(7);

        while (!isButtonPressed())
        {
            Hardware::delay(10);
        }
        Hardware::delay(50);

        uint32_t baseCycles = 20;
        uint32_t extraCycles = Random::random(0, 10);
        uint32_t totalCycles = baseCycles + extraCycles;

        uint32_t delayTime = 50;
        uint8_t currentLED = 0;

        for (uint32_t i = 0; i < totalCycles; i++)
        {
            currentLED = i % 6;
            Hardware::setMuxChannel(currentLED);
            Hardware::delay(delayTime);
            delayTime += 10;
        }

        for (uint8_t i = 0; i < 3; i++)
        {
            Hardware::setMuxChannel(currentLED);
            Hardware::delay(200);
            Hardware::setMuxChannel(6);
            Hardware::delay(200);
        }

        Hardware::setMuxChannel(currentLED);
        Hardware::delay(3000);
        Hardware::setMuxChannel(7);
    }
}