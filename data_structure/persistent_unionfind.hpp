#pragma once
#include <algorithm>
#include <data_structure/persistent_array.hpp>

struct PersistentUnionfind {
    int n;
    PersistentArray<int> v;

    PersistentUnionfind() : n(0), v(0) {}
    explicit PersistentUnionfind(int n) : n(n), v(n, -1) {}

    int merge(int a, int b, int t = -1) {
        int x = leader(a, t), y = leader(b, t);
        if (x == y) return x;
        if (-v.get(x, t) < -v.get(y, t)) std::swap(x, y);
        t = v.set(x, v.get(x, t) + v.get(y, t), t);
        return v.set(y, x, t);
    }

    bool same(int a, int b, int t = -1) {
        return leader(a, t) == leader(b, t);
    }

    int leader(int a, int t = -1) {
        if (v.get(a, t) < 0) return a;
        return leader(v.get(a, t), t);
    }

    int size(int a, int t = -1) {
        return -v.get(a, t);
    }
};
