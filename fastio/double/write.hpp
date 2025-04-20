#pragma once
#include <cstdint>
#include <fastio/unsigned/write.hpp>

static const int FASTIOPRECISION = 10;
inline FASTIO& operator<<(FASTIO& io, long double x) noexcept {
    io.reserve(18 + FASTIOPRECISION);
    if (x < 0) {
        *io.opos++ = '-';
        x = -x;
    }
    uint64_t u = x;
    io << u;
    *io.opos++ = '.';
    x -= u;
    for (int i = 0; i < FASTIOPRECISION; ++i) {
        x *= 10;
        *io.opos++ = '0' + ((uint8_t)x);
        x -= (uint8_t)x;
    }
    return io;
}

FASTIO& operator<<(FASTIO& io, double x) {
    io << static_cast<long double>(x);
    return io;
}

FASTIO& operator<<(FASTIO& io, float x) {
    io << static_cast<long double>(x);
    return io;
}
