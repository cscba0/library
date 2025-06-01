#pragma once
#include <algorithm>
#include <vector>

struct Unique {
    template <typename T>
    Unique(std::vector<T>& v) {
        std::sort(v.begin(), v.end());
        v.erase(std::unique(v.begin(), v.end()), v.end());
    }
};
