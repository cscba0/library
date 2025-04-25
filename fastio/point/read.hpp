#pragma once
#include <data_structure/point.hpp>
#include <fastio/base.hpp>

template <typename T>
inline FASTIO& operator>>(FASTIO& io, Point<T>& P) noexcept {
    io >> P.x >> P.y;
    return io;
}
