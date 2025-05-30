#pragma once
#include <type_traits>

template <typename T = void>
struct INF;

template <typename T>
constexpr T INF_CONST() {
    if constexpr (std::is_same_v<T, int>) {
        return 2147483647;
    } else if constexpr (std::is_same_v<T, long long>) {
        return 9223372036854775807LL;
    } else {
        static_assert(sizeof(T) == 0, "Unsupported type");
    }
}

template <>
struct INF<void> {
    operator int() const {
        return INF_CONST<int>();
    }

    operator long long() const {
        return INF_CONST<long long>();
    }
};

template <typename T>
struct INF {
    constexpr operator T() const {
        return INF<T>();
    }
};
