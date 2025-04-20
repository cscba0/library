#pragma once
#include <library/fastio/char/read.hpp>
#include <string>

inline FASTIO& operator>>(FASTIO& io, std::string& s) noexcept {
    io.seek();
    s = "";
    while (' ' < *io.ipos) {
        s += *io.ipos++;
    }
    return io;
}
