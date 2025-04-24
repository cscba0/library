#pragma once
#include <fastio/base.hpp>

template <typename T1, typename T2>
inline FASTIO& operator>>(FASTIO& io, std::pair<T1, T2>& P) noexcept {
    io >> P.first >> P.second;
    return io;
}
