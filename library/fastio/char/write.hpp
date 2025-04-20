#pragma once
#include <library/fastio/base.hpp>

inline FASTIO& operator<<(FASTIO& io, char c) noexcept {
    io.reserve(1);
    *io.opos++ = c;
    return io;
}
