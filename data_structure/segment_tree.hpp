#pragma once
#include <cstdint>
#include <vector>

template <typename T, auto op, auto e>
struct SegmentTree {
    int n;
    std::vector<T> v;
    explicit SegmentTree() : SegmentTree(0) {}
    explicit SegmentTree(int n) : SegmentTree(std::vector<T>(n, e())) {}
    explicit SegmentTree(const std::vector<T>& _v) : n(InitialN(_v.size())), v(n * 2, e()) {
        for (uint32_t i = 0; i < _v.size(); ++i) {
            v[i + n] = _v[i];
        }
        for (int i = n - 1; i; --i) {
            v[i] = op(v[i << 1], v[(i << 1) | 1]);
        }
    }

    int InitialN(size_t siz) {
        int n = 1;
        while (n < siz) {
            n <<= 1;
        }
        return n;
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

    int max_right(int l, auto f) const {
        if (l == n) return n;
        l += n;
        T sm = e();
        do {
            while ((l & 1) == 0) l >>= 1;
            if (!f(op(sm, v[l]))) {
                while (l < n) {
                    l <<= 1;
                    if (f(op(sm, v[l]))) {
                        sm = op(sm, v[l]);
                        ++l;
                    }
                }
                return l - n;
            }
            sm = op(sm, v[l]);
            ++l;
        } while ((l & -l) != l);
        return n;
    }

    int min_left(int r, auto f) const {
        if (r == 0) return 0;
        r += n;
        T sm = e();
        do {
            --r;
            while (r > 1 && (r & 1)) r >>= 1;
            if (!f(op(v[r], sm))) {
                while (r < n) {
                    r = ((r << 1) + 1);
                    if (f(op(v[r], sm))) {
                        sm = op(v[r], sm);
                        r--;
                    }
                }
                return r + 1 - n;
            }
            sm = op(v[r], sm);
        } while ((r & -r) != r);
        return 0;
    }
};
