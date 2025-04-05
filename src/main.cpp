#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include "Trinkspiel/trinkspiel.hpp"
#include "Hardware/hardware.hpp"
#include "Random/random.hpp"
#include <avr/io.h>

constexpr uint16_t ADC_THRESHOLD = 875;

int main() 
{
  Hardware::init();

  for (uint8_t i = 0; i < 2; i++)
  {
        
    Hardware::setMuxChannel(6);
    Hardware::delay(100); 

    Hardware::setMuxChannel(7);
    Hardware::delay(100); 
  }

  uint16_t seed = Hardware::readADC(4);
  Random::srand(seed);

  while (true) 
    {
        uint16_t triggerValue = Hardware::readADC(Hardware::PIN_BUTTON);
        if (triggerValue < ADC_THRESHOLD)
        {
            Trinkspiel::run();

            while (Hardware::readADC(Hardware::PIN_BUTTON) < ADC_THRESHOLD)
            {
                Hardware::delay(10);
            }
        }
        Hardware::delay(50);
    }
    
    return 0;
}
