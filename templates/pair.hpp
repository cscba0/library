#pragma once
#include <utility>

template <typename T1, typename T2>
std::pair<T1, T2> operator+(const std::pair<T1, T2>& x, const std::pair<T1, T2> y) {
    return std::pair<T1, T2>(x.first + y.first, x.second + y.second);
}
template <typename T1, typename T2>
std::pair<T1, T2>& operator+=(std::pair<T1, T2>& x, const std::pair<T1, T2> y) {
    x = x + y;
    return x;
}

template <typename T1, typename T2>
std::pair<T1, T2> operator-(const std::pair<T1, T2>& x, const std::pair<T1, T2> y) {
    return std::pair<T1, T2>(x.first - y.first, x.second - y.second);
}
template <typename T1, typename T2>
std::pair<T1, T2>& operator-=(std::pair<T1, T2>& x, const std::pair<T1, T2> y) {
    x = x - y;
    return x;
}

template <typename T1, typename T2>
std::pair<T1, T2>& operator++(std::pair<T1, T2>& x) {
    ++x.first;
    ++x.second;
    return x;
}
template <typename T1, typename T2>
std::pair<T1, T2>& operator--(std::pair<T1, T2>& x) {
    --x.first;
    --x.second;
    return x;
}
