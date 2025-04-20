#pragma once
#include <algorithm>
#include <stack>
#include <vector>

struct weighted_unionfind {
    int n;
    std::vector<int> v;
    std::vector<long long> w;
    std::stack<std::pair<int, int>> h;

    weighted_unionfind() : n(0) {}
    explicit weighted_unionfind(int n) : n(n), v(n, -1), w(n, 0) {}

    int merge(int a, int b, long long W) {
        auto [x, sx] = leader(a);
        auto [y, sy] = leader(b);
        h.push({x, v[x]});
        h.push({y, v[y]});
        h.push({x, w[x]});
        h.push({y, w[y]});
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
    long long weight(int a, int b) {
        return leader(b).second - leader(a).second;
    }

    std::pair<int, long long> leader(int a, long long sum = 0) {
        if (v[a] < 0) return {a, sum};
        return leader(v[a], sum + w[a]);
    }

    int size(int a) {
        return -v[leader(a).first];
    }

    bool undo() {
        bool flg = false;
        for (int i = 0; i < 2; i++) {
            w[h.top().first] = h.top().second;
        }
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
