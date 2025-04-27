#pragma once
#include <algorithm>
#include <vector>

template <typename T = int64_t>
struct UnionFindWithPotential {
    int n;
    std::vector<int> v;
    std::vector<T> w;

    UnionFindWithPotential() : n(0) {}
    explicit UnionFindWithPotential(int n) : n(n), v(n, -1), w(n, 0) {}

    int merge(int a, int b, T W) {
        auto [x, sx] = leader(a);
        auto [y, sy] = leader(b);
        if (x == y) return x;
        W = -W;
        if (-v[x] < -v[y]) {
            std::swap(x, y);
            std::swap(sx, sy);
            W = -W;
        }
        v[x] += v[y];
        v[y] = x;
        w[y] = (sx - sy) - W;
        return x;
    }

    bool same(int a, int b) {
        return leader(a).first == leader(b).first;
    }

    // return b - a
    T weight(int a, int b) {
        return leader(b).second - leader(a).second;
    }

    std::pair<int, T> leader(int a, T sum = 0) {
        if (v[a] < 0) return {a, sum};
        return leader(v[a], sum + w[a]);
    }

    int size(int a) {
        return -v[leader(a).first];
    }
};
