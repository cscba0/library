#pragma once
#include <cstdint>
#include <fastio/floating/precision.hpp>
#include <fastio/unsigned/write.hpp>

template <std::floating_point T>
FASTIO& operator<<(FASTIO& io, T x) {
    io.reserve(21 + FastIOPrecision);
    if (x < 0) {
        *io.opos++ = '-';
        x = -x;
    }
    uint64_t u = x;
    io << u;
    *io.opos++ = '.';
    x -= u;
    for (int i = 0; i < FastIOPrecision; ++i) {
        x *= 10;
        *io.opos++ = '0' + static_cast<uint8_t>(x);
        x -= static_cast<uint8_t>(x);
    }
    return io;
}
