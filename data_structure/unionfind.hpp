#pragma once
#include <algorithm>
#include <stack>
#include <vector>

struct UnionFind {
    int n;
    std::vector<int> v;
    std::stack<std::pair<int, int>> h;

    UnionFind() : n(0) {}
    explicit UnionFind(int n) : n(n), v(n, -1) {}

    int merge(int a, int b) {
        int x = leader(a), y = leader(b);
        h.push({x, v[x]});
        h.push({y, v[y]});
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

    bool undo() {
        bool flg = false;
        for (int i = 0; i < 2; i++) {
            if (v[h.top().first] != h.top().second) {
                flg = true;
            }
            v[h.top().first] = h.top().second;
            h.pop();
        }
        return flg;
    }
};
