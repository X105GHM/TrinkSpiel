#ifndef HARDWARE_HPP
#define HARDWARE_HPP

#include <stdint.h>

namespace Hardware
{
    enum class PinMode : uint8_t
    {
        INPUT = 0,
        OUTPUT = 1
    };

    constexpr uint8_t PIN_S0 = 2;
    constexpr uint8_t PIN_S1 = 1;
    constexpr uint8_t PIN_S2 = 0;
    constexpr uint8_t PIN_BUTTON = 3;
    constexpr uint8_t PIN_ADC = 4;

    void pinMode(uint8_t pin, PinMode mode) noexcept;

    void digitalWrite(uint8_t pin, bool value) noexcept;

    [[nodiscard]] bool digitalRead(uint8_t pin) noexcept;

    void setMuxChannelSimultaneous(uint8_t channel) noexcept;

    [[nodiscard]] uint32_t millis() noexcept;

    void delay(uint32_t ms) noexcept;

    inline void delayMicroseconds(uint16_t us) noexcept;
    
    void initADC();

    uint16_t readADC(uint8_t channel);

    void init() noexcept;

    void setMuxChannel(uint8_t channel) noexcept;
}

#endif // HARDWARE_HPP
