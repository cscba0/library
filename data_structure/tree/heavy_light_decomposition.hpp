#pragma once
#include <data_structure/segment_tree.hpp>
#include <stack>
#include <vector>

template <typename T, auto op, auto e>
struct HeavyLightDecomposition {
    int n;
    std::vector<int> euler, dep, per, root, siz;
    std::vector<std::pair<int, int>> ran;
    SegmentTree<T, op, e> seg, rev;
    explicit HeavyLightDecomposition(std::vector<std::vector<int>> g) : HeavyLightDecomposition(g, std::vector<T>(g.size(), e())) {}
    explicit HeavyLightDecomposition(std::vector<std::vector<int>> g, const std::vector<T>& Vec)
        : n(g.size()),
          dep(n, -1),
          per(n, -1),
          root(n, -1),
          siz(n, 1) {
        ran.resize(n, {-1, -1});
        euler.reserve(n);
        {
            per[0] = 0;
            dep[0] = 0;
            std::stack<std::pair<int, bool>> st;
            st.emplace(0, true);
            while (!st.empty()) {
                auto [u, flg] = st.top();
                st.pop();
                if (flg) {
                    for (int v : g[u]) {
                        if (v != per[u]) {
                            per[v] = u;
                            dep[v] = dep[u] + 1;
                            st.push({v, false});
                            st.push({v, true});
                        }
                    }
                } else {
                    siz[per[u]] += siz[u];
                }
            }
        }
        std::vector<T> vec;
        {
            std::stack<std::tuple<int, int, bool>> st;
            st.emplace(0, 0, false);
            st.emplace(0, 0, true);
            while (!st.empty()) {
                auto [u, r, flg] = st.top();
                st.pop();
                if (flg) {
                    vec.emplace_back(Vec[u]);
                    ran[u].first = static_cast<int>(euler.size());
                    euler.emplace_back(u);
                    root[u] = r;
                    int V = -1, S = -1;
                    for (int v : g[u]) {
                        if (v == per[u]) continue;
                        if (S < siz[v]) {
                            S = siz[v];
                            V = v;
                        }
                    }
                    for (int v : g[u]) {
                        if (v == per[u]) continue;
                        if (v != V) {
                            st.emplace(v, v, false);
                            st.emplace(v, v, true);
                        }
                    }
                    if (V != -1) {
                        st.emplace(V, r, false);
                        st.emplace(V, r, true);
                    }
                } else {
                    ran[u].second = static_cast<int>(euler.size()) - 1;
                }
            }
        }
        seg = std::move(SegmentTree<T, op, e>(vec));
        reverse(vec.begin(), vec.end());
        rev = std::move(SegmentTree<T, op, e>(vec));
    }

    T operator[](int p) const {
        return seg[ran[p].first];
    }

    void set(int p, T x) {
        seg.set(ran[p].first, x);
        rev.set(n - ran[p].first - 1, x);
    }

    void add(int p, T x) {
        seg.add(ran[p].first, x);
        rev.add(n - ran[p].first - 1, x);
    }

    T operator()(int u, int v) {
        T L{e()}, R{e()};
        while (root[u] != root[v]) {
            if (dep[root[v]] < dep[root[u]]) {
                L = op(L, rev(n - ran[u].first - 1, n - ran[root[u]].first));
                u = per[root[u]];
            } else {
                R = op(seg(ran[root[v]].first, ran[v].first + 1), R);
                v = per[root[v]];
            }
        }
        if (ran[v].first < ran[u].first) {
            L = op(L, rev(n - ran[u].first - 1, n - ran[v].first));
        } else {
            R = op(seg(ran[u].first, ran[v].first + 1), R);
        }
        return op(L, R);
    }

    std::vector<std::pair<int, int>> route(int u, int v) {
        std::vector<std::pair<int, int>> res;
        while (root[u] != root[v]) {
            if (dep[root[v]] < dep[root[u]]) {
                res.emplace_back(std::make_pair(ran[root[u]].first, ran[u].first));
                u = per[root[u]];
            } else {
                res.emplace_back(std::make_pair(ran[root[v]].first, ran[v].first));
                v = per[root[v]];
            }
        }
        res.emplace_back(std::make_pair(
            std::min(ran[u].first, ran[v].first),
            std::max(ran[u].first, ran[v].first)));
        return res;
    }

    T part(int u) {
        return seg(ran[u].first, ran[u].second + 1);
    }

    int lca(int u, int v) {
        while (root[u] != root[v]) {
            if (dep[root[v]] < dep[root[u]]) {
                u = per[root[u]];
            } else {
                v = per[root[v]];
            }
        }
        return euler[std::min(ran[u].first, ran[v].first)];
    }
};
