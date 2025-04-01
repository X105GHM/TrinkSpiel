#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include "Trinkspiel/trinkspiel.hpp"
#include "Hardware/hardware.hpp"
#include "Random/random.hpp"
#include <avr/io.h>

int main() 
{
  Hardware::init();

  for (uint8_t i = 0; i < 2; i++)
  {
        
    Hardware::setMuxChannel(6);
    Hardware::delay(200); 

    Hardware::setMuxChannel(7);
    Hardware::delay(200); 
  }

  Random::srand(Hardware::millis());


  while (true) 
  {
    Trinkspiel::run();
    Hardware::delay(500);
  }
    
  return 0;
}
