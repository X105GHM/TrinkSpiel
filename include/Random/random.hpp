#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <stdint.h>

namespace Random 
{
    void srand(uint32_t seed) noexcept;

    [[nodiscard]] uint32_t rand() noexcept;

    [[nodiscard]] uint32_t random(uint32_t min, uint32_t max) noexcept;
}

#endif // RANDOM_HPP
