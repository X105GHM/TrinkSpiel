#include "Hardware/hardware.hpp"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint32_t g_millis = 0;

namespace Hardware
{

    void pinMode(uint8_t pin, PinMode mode) noexcept
    {
        if (mode == PinMode::OUTPUT)
        {
            DDRB |= (1 << pin);
        }
        else
        {
            DDRB &= ~(1 << pin);
        }
    }

    void digitalWrite(uint8_t pin, bool value) noexcept
    {
        if (value)
        {
            PORTB |= (1 << pin);
        }
        else
        {
            PORTB &= ~(1 << pin);
        }
    }

    bool digitalRead(uint8_t pin) noexcept
    {
        return (PINB & (1 << pin)) != 0;
    }

    inline void initTimer() noexcept
    {
        TCCR0A = (1 << WGM01);
        TCCR0B = (1 << CS01) | (1 << CS00);
        OCR0A = (F_CPU / 64 / 1000) - 1;
        TIMSK |= (1 << OCIE0A);
    }

    void setMuxChannel(uint8_t channel) noexcept 
    {
        constexpr uint8_t muxMask = (1 << PIN_S0) | (1 << PIN_S1) | (1 << PIN_S2);

        uint8_t value = (((channel >> 0) & 0x01) << PIN_S0) |
                        (((channel >> 1) & 0x01) << PIN_S1) |
                        (((channel >> 2) & 0x01) << PIN_S2);
     
        PORTB = (PORTB & ~muxMask) | value;
    }

    ISR(TIM0_COMPA_vect)
    {
        g_millis++;
    }

    uint32_t millis() noexcept
    {
        uint32_t ms;
        uint8_t sreg = SREG;
        cli();
        ms = g_millis;
        SREG = sreg;
        return ms;
    }

    void delay(uint32_t ms) noexcept {
        while(ms--) {
            _delay_ms(1);
        }
    }

    inline void delayMicroseconds(uint16_t us) noexcept
    {
        uint16_t iterations = (us + 3) / 4;
        __asm__ volatile(
            "1: sbiw %0, 1 \n\t"
            "brne 1b"
            : "=w"(iterations)
            : "0"(iterations));
    }

    void initADC()
    {
        ADMUX = 0;
        ADCSRA = (1 << ADEN) | (1 << ADPS1) | (1 << ADPS0);
    }

    uint16_t readADC(uint8_t channel)
    {
        ADMUX = (ADMUX & 0xF8) | (channel & 0x07);
        delayMicroseconds(100);
        ADCSRA |= (1 << ADSC);
        while (ADCSRA & (1 << ADSC))
            ;
        uint8_t low = ADCL;
        uint8_t high = ADCH;
        return (static_cast<uint16_t>(high) << 8) | low;
    }

    void init() noexcept
    {
        initTimer();
        sei();

        pinMode(PIN_S0, PinMode::OUTPUT);
        pinMode(PIN_S1, PinMode::OUTPUT);
        pinMode(PIN_S2, PinMode::OUTPUT);
        pinMode(PIN_ADC, PinMode::INPUT);
        PORTB &= ~(1 << PIN_ADC);

        pinMode(PIN_BUTTON, PinMode::INPUT);
        PORTB |= (1 << PIN_BUTTON);

        initADC();
    }
}
