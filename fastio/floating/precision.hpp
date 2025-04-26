#pragma once
#include <fastio/base.hpp>

static int FastIOPrecision = 10;

struct precision {
    int n;
    constexpr precision(int _n) : n(_n) {}
};

inline FASTIO& operator<<(FASTIO& io, const precision p) {
    FastIOPrecision = p.n;
    return io;
}
