#pragma once
#include <vector>

template <typename T, auto op, auto e>
struct Segtree {
    int n;
    std::vector<T> v;
    explicit Segtree(int n) : Segtree(std::vector<T>(n, e())) {}
    explicit Segtree(const std::vector<T>& _v) : n(_v.size()), v(_v.size() * 2, e()) {
        for (int i = 0; i < n; ++i) {
            v[i + n] = _v[i];
        }
        for (int i = n - 1; i; --i) {
            v[i] = op(v[i << 1], v[(i << 1) | 1]);
        }
    }

    T operator[](int p) const {
        return v[p + n];
    }

    void set(int p, T x) {
        p += n;
        v[p] = x;
        for (p >>= 1; p; p >>= 1) {
            v[p] = op(v[p << 1], v[(p << 1) | 1]);
        }
    }

    void add(int p, T x) {
        p += n;
        v[p] += x;
        for (p >>= 1; p; p >>= 1) {
            v[p] = op(v[p << 1], v[(p << 1) | 1]);
        }
    }

    T operator()(int l, int r) const {
        T L{e()}, R{e()};
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) L = op(L, v[l++]);
            if (r & 1) R = op(v[--r], R);
        }
        return op(L, R);
    }

    int max_right(int L, auto f) const {
        int l = n + L, w = 1, sum = e();
        for (; L + w <= n; l >>= 1, w <<= 1)
            if (l & 1) {
                if (not f(op(sum, v[l]))) break;
                sum = op(sum, v[l++]);
                L += w;
            }
        while (l <<= 1, w >>= 1) {
            if (L + w <= n && f(op(sum, v[l]))) {
                sum = op(sum, v[l++]);
                L += w;
            }
        }
        return L;
    }

    int min_left(int R, auto f) const {
        int r = n + R, w = 1, sum = e();
        for (; R - w >= 0; r >>= 1, w <<= 1)
            if (r & 1) {
                if (not f(op(v[r - 1], sum))) break;
                sum = op(v[--r], sum);
                R -= w;
            }
        while (r <<= 1, w >>= 1) {
            if (R - w >= 0 && f(op(v[r - 1], sum))) {
                sum = op(v[--r], sum);
                R -= w;
            }
        }
        return R;
    }
};
