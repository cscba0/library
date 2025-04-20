#pragma once

template <typename T>
bool chmax(T& x, const T y) {
    if (x < y) {
        x = y;
        return true;
    }
    return false;
}
template <typename T>
bool chmin(T& x, const T y) {
    if (x > y) {
        x = y;
        return true;
    }
    return false;
}
