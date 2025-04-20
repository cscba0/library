#pragma once
#include <cstdint>
#include <fastio/unsigned/write.hpp>

inline FASTIO& operator<<(FASTIO& io, __int128 x) noexcept {
    io.reserve(40);
    if (x < 0) {
        *io.opos++ = '-';
        x = -x;
    }
    if (x / 1'0000'0000'0000'0000 != 0) {
        if (x / 1'0000'0000'0000'0000 / 1'0000'0000'0000'0000 != 0) {
            FastWrite(io, uint64_t(x / 1'0000'0000'0000'0000 / 1'0000'0000'0000'0000));
            x %= __int128(1'0000'0000'0000'0000) * __int128(1'0000'0000'0000'0000);
            FastWrite_(io, x / 10000 / 10000 / 10000 / 10000 / 10000 / 10000 / 10000 % 10000);
            FastWrite_(io, x / 10000 / 10000 / 10000 / 10000 / 10000 / 10000 % 10000);
            FastWrite_(io, x / 10000 / 10000 / 10000 / 10000 / 10000 % 10000);
            FastWrite_(io, x / 10000 / 10000 / 10000 / 10000 % 10000);
            FastWrite_(io, x / 10000 / 10000 / 10000 % 10000);
            FastWrite_(io, x / 10000 / 10000 % 10000);
            FastWrite_(io, x / 10000 % 10000);
            FastWrite_(io, x % 10000);
        } else {
            FastWrite(io, uint64_t(x / 1'0000'0000'0000'0000));
            x %= 1'0000'0000'0000'0000;
            FastWrite_(io, x / 10000 / 10000 / 10000 % 10000);
            FastWrite_(io, x / 10000 / 10000 % 10000);
            FastWrite_(io, x / 10000 % 10000);
            FastWrite_(io, x % 10000);
        }
    } else {
        FastWrite(io, uint64_t(x));
    }
    return io;
}
