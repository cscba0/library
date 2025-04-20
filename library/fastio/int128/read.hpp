#pragma once
#include <bit>
#include <cstdint>
#include <library/fastio/base.hpp>

inline FASTIO& operator>>(FASTIO& io, __int128& x) noexcept {
    io.seek();
    bool neg = false;
    if (*io.ipos == '-') {
        neg = true;
        ++io.ipos;
    }
    x = 0;
    while (true) {
        uint64_t cur = *reinterpret_cast<uint64_t*>(io.ipos);
        uint8_t cnt = std::countr_zero((~cur >> 4) & 0x0101010101010101);
        cur <<= 64 - cnt;
        cur &= 0x0f0f0f0f0f0f0f0f;
        cur = (cur * 10 + (cur >> 8)) & 0x00ff00ff00ff00ff;
        cur = (cur * 100 + (cur >> 16)) & 0x0000ffff0000ffff;
        cur = (cur * 10000 + (cur >> 32)) & 0x00000000ffffffff;
        if (cnt == 64) {
            x = x * 100000000 + cur;
            io.ipos += 8;
        } else {
            break;
        }
    }
    for (; '0' <= *io.ipos && *io.ipos <= '9'; ++io.ipos) {
        x = x * 10 + *io.ipos - '0';
    }
    if (neg) {
        x = -x;
    }
    return io;
}
