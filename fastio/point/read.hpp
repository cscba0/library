#pragma once
#include <fastio/base.hpp>
#include <math/point.hpp>

template <typename T>
inline FASTIO& operator>>(FASTIO& io, Point<T>& P) noexcept {
    io >> P.x >> P.y;
    return io;
}
