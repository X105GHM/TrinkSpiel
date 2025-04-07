#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <stdint.h>

namespace Random
{

    void init() noexcept;

    uint32_t next() noexcept;

    uint32_t random(uint32_t min, uint32_t max) noexcept;

}

#endif // RANDOM_HPP
