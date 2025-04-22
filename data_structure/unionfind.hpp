#pragma once
#include <algorithm>
#include <vector>

struct Unionfind {
    int n;
    std::vector<int> v;

    Unionfind() : n(0) {}
    explicit Unionfind(int n) : n(n), v(n, -1) {}

    int merge(int a, int b) {
        int x = leader(a), y = leader(b);
        if (x == y) return x;
        if (-v[x] < -v[y]) std::swap(x, y);
        v[x] += v[y];
        v[y] = x;
        return x;
    }

    bool same(int a, int b) {
        return leader(a) == leader(b);
    }

    int leader(int a) {
        if (v[a] < 0) return a;
        return leader(v[a]);
    }

    int size(int a) {
        return -v[leader(a)];
    }
};
