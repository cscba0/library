#pragma once
#include <cstdint>
#include <fastio/unsigned/write.hpp>

inline FASTIO& operator<<(FASTIO& io, __int128 x) noexcept {
    io.reserve(40);
    if (x < 0) {
        *io.opos++ = '-';
        x = -x;
    }
    if (x < 1'0000'0000'0000'0000U) {
        FastWrite(io, static_cast<uint64_t>(x));
    } else if (x / 1'0000'0000'0000'0000U < 1'0000'0000'0000'0000U) {
        FastWrite(io, static_cast<uint64_t>(x / 1'0000'0000'0000'0000U));
        FastWrite_(io, static_cast<uint64_t>(x / 1'0000'0000'0000U % 1'0000));
        FastWrite_(io, static_cast<uint64_t>(x / 1'0000'0000U % 1'0000));
        FastWrite_(io, static_cast<uint64_t>(x / 1'0000U % 1'0000));
        FastWrite_(io, static_cast<uint64_t>(x % 1'0000));
    } else {
        FastWrite(io, static_cast<uint64_t>(x / 1'0000'0000'0000'0000U / 1'0000'0000'0000'0000U));
        FastWrite_(io, static_cast<uint64_t>(x / 1'0000'0000'0000'0000U / 1'0000'0000'0000 % 10000));
        FastWrite_(io, static_cast<uint64_t>(x / 1'0000'0000'0000'0000U / 1'0000'0000 % 10000));
        FastWrite_(io, static_cast<uint64_t>(x / 1'0000'0000'0000'0000U / 1'0000 % 10000));
        FastWrite_(io, static_cast<uint64_t>(x / 1'0000'0000'0000'0000U % 1'0000));
        FastWrite_(io, static_cast<uint64_t>(x / 1'0000'0000'0000U % 1'0000));
        FastWrite_(io, static_cast<uint64_t>(x / 1'0000'0000U % 1'0000));
        FastWrite_(io, static_cast<uint64_t>(x / 1'0000U % 1'0000));
        FastWrite_(io, static_cast<uint64_t>(x % 1'0000));
    }
    return io;
}
