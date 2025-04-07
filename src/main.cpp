#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include "Trinkspiel/trinkspiel.hpp"
#include "Hardware/hardware.hpp"
#include "Random/random.hpp"
#include <avr/io.h>

constexpr uint16_t ADC_THRESHOLD = 870;

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

  Hardware:: delay(250);
  
  while (true) 
    {
        uint16_t triggerValue = Hardware::readADC(Hardware::PIN_BUTTON);
        if (triggerValue < ADC_THRESHOLD)
        {
          Random::init();
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
