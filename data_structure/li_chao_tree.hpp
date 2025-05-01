#pragma once
#include <stack>
#include <vector>

template <typename T, auto e>
struct LiChaoTree {
    int n;
    int siz;
    std::vector<T> cmp;
    struct node {
        T a, b;
        node(T _a, T _b) : a(_a), b(_b) {}
        node() {}
        T get(T x) {
            return x * a + b;
        }
    };
    std::vector<node> v;
    LiChaoTree(const std::vector<T>& vec) : cmp(vec) {
        sort(cmp.begin(), cmp.end());
        cmp.erase(unique(cmp.begin(), cmp.end()), cmp.end());
        n = cmp.size();
        siz = (1 << (std::__lg(std::max(1, n)) + 1)) << 1;
        v = std::vector<node>(siz, node{0, e()});
    }
    void add(T a, T b, int c = 1, T l = 0, T r = -1) {
        if (r == -1) {
            r = n;
        }
        while (c < siz) {
            if (r <= l + 1) break;
            if (b == e()) return;
            node& cur = v[c];
            T mid = (l + r) >> 1;
            T L = a * cmp[l] + b;
            T M = a * cmp[mid] + b;
            T R = a * cmp[(r - 1)] + b;
            T cL = cur.get(cmp[l]);
            T cM = cur.get(cmp[mid]);
            T cR = cur.get(cmp[r - 1]);
            if (cL <= L && cR <= R) {
                return;
            }
            if (L <= cL && R <= cR) {
                std::swap(cur.a, a);
                std::swap(cur.b, b);
                return;
            }
            if (L <= cL) {
                if (M <= cM) {
                    std::swap(cur.a, a);
                    std::swap(cur.b, b);
                    c = (c << 1) | 1;
                    l = mid;
                } else {
                    c = (c << 1);
                    r = mid;
                }
            } else {
                if (M <= cM) {
                    std::swap(cur.a, a);
                    std::swap(cur.b, b);
                    c = (c << 1);
                    r = mid;
                } else {
                    c = (c << 1) | 1;
                    l = mid;
                }
            }
        }
        if (c < siz) {
            if (a * cmp[l] + b < v[c].get(cmp[l])) {
                std::swap(a, v[c].a);
                std::swap(b, v[c].b);
            }
        }
    }

    void add(T a, T b, T L, T R) {
        std::stack<std::tuple<int, T, T>> st;
        st.emplace(1, 0, n);
        while (!st.empty()) {
            auto [c, l, r] = st.top();
            st.pop();
            if (siz <= c) continue;
            if (cmp[r - 1] < L || R <= cmp[l]) continue;
            if (L <= cmp[l] && cmp[r - 1] < R) {
                add(a, b, c, l, r);
                continue;
            }
            T mid = (l + r) >> 1;
            st.emplace((c << 1), l, mid);
            st.emplace((c << 1) | 1, mid, r);
        }
    }

    T operator()(T x) {
        int c = 1;
        T l = 0, r = n;
        T res{e()};
        while (c < siz) {
            res = std::min(res, v[c].get(x));
            T mid = (l + r) >> 1;
            if (x < cmp[mid]) {
                r = mid;
                c = (c << 1);
            } else {
                l = mid;
                c = (c << 1) | 1;
            }
        }
        return res;
    }
};
