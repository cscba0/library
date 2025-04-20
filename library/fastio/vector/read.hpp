#pragma once
#include <library/fastio/base.hpp>
#include <vector>

template <typename T>
inline FASTIO& operator>>(FASTIO& io, std::vector<T>& v) noexcept {
    for (auto& x : v) {
        io >> x;
    }
    return io;
}
