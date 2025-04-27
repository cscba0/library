#pragma once
#include <fastio/floating/write.hpp>
#include <math/fraction.hpp>

template <typename T>
inline FASTIO& operator<<(FASTIO& io, const Fraction<T>& x) noexcept {
    long double c = static_cast<long double>(x.x) / static_cast<long double>(x.y);
    io << c;
    return io;
}
