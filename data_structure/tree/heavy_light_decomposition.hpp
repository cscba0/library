#pragma once
#include <cstdint>
#include <queue>
#include <stack>
#include <vector>

template <typename T, auto op, auto e>
struct HeavyLightDecomposition {
    int n, N;
    std::vector<int> euler, dep, per, root, siz, pos;
    std::vector<std::pair<int, int>> ran;
    std::vector<T> seg, rev;
    struct node {
        T v{e()}, r{e()};
        int parent{0}, left{-1}, right{-1}, depth{0};
        bool flg{false}, begin{false};
        node() {}
        node(int _parent) : parent(_parent) {}
        node(int _parent, int _depth) : parent(_parent), depth(_depth) {}
        node(int _parent, int _depth, bool _flg) : parent(_parent), depth(_depth), flg(_flg) {}
    };
    std::vector<node> nd;
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
        N = (1 << (std::__lg(std::max(1, n)) + 1)) << 1;
        std::vector<int> sum = siz;
        for (uint32_t i = 1; i < sum.size(); ++i) {
            sum[i] += sum[i - 1];
        }
        pos.resize(N);
        build(vec, sum, n, N);
        for (int i = 0; i < n; ++i) {
            nd[pos[i]].v = vec[i];
            nd[pos[i]].r = vec[i];
        }
        for (int i = pos[0] - 1; i; --i) {
            nd[i].v = op(nd[nd[i].left].v, nd[nd[i].right].v);
            nd[i].r = op(nd[nd[i].right].r, nd[nd[i].left].r);
        }
        // {
        //     seg.resize(N * 2);
        //     for (uint32_t i = 0; i < vec.size(); ++i) {
        //         seg[i + N] = vec[i];
        //     }
        //     for (int i = N - 1; i; --i) {
        //         seg[i] = op(seg[i << 1], seg[(i << 1) | 1]);
        //     }
        // }
        // reverse(vec.begin(), vec.end());
        // {
        //     rev.resize(N * 2);
        //     for (uint32_t i = 0; i < vec.size(); ++i) {
        //         rev[i + N] = vec[i];
        //     }
        //     for (int i = N - 1; i; --i) {
        //         rev[i] = op(rev[i << 1], rev[(i << 1) | 1]);
        //     }
        // }
    }

    void build(const std::vector<T>& vec, const std::vector<int>& sum, int n, int N) {
        std::queue<std::tuple<int, int, int>> q;
        nd.reserve(N * 4);
        nd.emplace_back(node{});
        nd.emplace_back(node{});
        q.emplace(1, 0, n);
        int last = -1;
        while (!q.empty()) {
            auto [c, l, r] = q.front();
            q.pop();
            if (nd[c].depth != last) {
                nd[c].begin = true;
                last = nd[c].depth;
            }
            if (l + 1 == r) {
                pos[l] = c;
                continue;
            }
            int cnt = sum[r - 1] - (l == 0 ? 0 : sum[l - 1]);
            cnt >>= 1;
            cnt += (l == 0 ? 0 : sum[l - 1]);
            int mid{0};
            {
                int lft = l + 1, rht = r - 1;
                while (lft < rht) {
                    int m = (lft + rht) >> 1;
                    if (sum[m] <= cnt) {
                        lft = m + 1;
                    } else {
                        rht = m;
                    }
                }
                mid = lft;
            }
            int cur = nd.size();
            nd[c].left = cur;
            nd[c].right = cur + 1;
            nd.emplace_back(node{c, nd[c].depth + 1, false});
            nd.emplace_back(node{c, nd[c].depth + 1, true});
            q.emplace(cur, l, mid);
            q.emplace(cur + 1, mid, r);
        }
    }

    T operator[](int p) const {
        return seg[ran[p].first];
    }

    void set(int p, T x) {
        {
            int c = pos[ran[p].first];
            nd[c].v = x;
            for (c = nd[c].parent; c; c = nd[c].parent) {
                nd[c].v = op(nd[nd[c].left].v, nd[nd[c].right].v);
                nd[c].r = op(nd[nd[c].right].r, nd[nd[c].left].r);
            }
        }
        // int P = p;
        // p = ran[p].first + N;
        // seg[p] = x;
        // for (p >>= 1; p; p >>= 1) {
        //     seg[p] = op(seg[p << 1], seg[(p << 1) | 1]);
        // }
        // p = n - ran[P].first - 1 + N;
        // rev[p] = x;
        // for (p >>= 1; p; p >>= 1) {
        //     rev[p] = op(rev[p << 1], rev[(p << 1) | 1]);
        // }
    }

    void add(int p, T x) {
        int P = p;
        p = ran[p].first + N;
        seg[p] += x;
        for (p >>= 1; p; p >>= 1) {
            seg[p] = op(seg[p << 1], seg[(p << 1) | 1]);
        }
        p = n - ran[P].first - 1 + N;
        rev[p] += x;
        for (p >>= 1; p; p >>= 1) {
            rev[p] = op(rev[p << 1], rev[(p << 1) | 1]);
        }
    }

    T get(bool flg, int l, int r) {
        T L{e()}, R{e()};
        if (l == 0) {
            r = pos[r];
            if (flg) {
                while (!nd[r].begin) {
                    if (nd[r].flg) {
                        R = op(nd[--r].v, R);
                    }
                    r = nd[r].parent;
                }
                return R;
            } else {
                while (!nd[r].begin) {
                    if (nd[r].flg) {
                        R = op(R, nd[--r].r);
                    }
                    r = nd[r].parent;
                }
                return R;
            }
        } else {
            --l;
            l = pos[l];
            r = pos[r];
            if (flg) {
                while (nd[l].depth > nd[r].depth) {
                    if (!nd[l].flg) {
                        L = op(L, nd[l].v);
                    }
                    l = nd[l].parent;
                }
                while (nd[r].depth > nd[l].depth) {
                    if (nd[r].flg) {
                        R = op(nd[r].v, R);
                    }
                    r = nd[r].parent;
                }
                for (; l + 1 < r; l = nd[l].parent, r = nd[r].parent) {
                    if (!nd[l].flg) {
                        L = op(L, nd[l].v);
                    }
                    if (nd[r].flg) {
                        R = op(nd[r].v, R);
                    }
                }
                return op(L, R);
            } else {
                while (nd[l].depth > nd[r].depth) {
                    if (!nd[l].flg) {
                        L = op(nd[l].v, L);
                    }
                    l = nd[l].parent;
                }
                while (nd[r].depth > nd[l].depth) {
                    if (nd[r].flg) {
                        R = op(R, nd[r].v);
                    }
                    r = nd[r].parent;
                }
                for (; l + 1 < r; l = nd[l].parent, r = nd[r].parent) {
                    if (!nd[l].flg) {
                        L = op(nd[l].v, L);
                    }
                    if (nd[r].flg) {
                        R = op(R, nd[r].v);
                    }
                }
                return op(R, L);
            }
        }
        // for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        //     if (l & 1) L = op(L, v[l++]);
        //     if (r & 1) R = op(v[--r], R);
        // }
        return op(L, R);
    }

    T operator()(int u, int v) {
        T L{e()}, R{e()};
        while (root[u] != root[v]) {
            if (dep[root[v]] < dep[root[u]]) {
                L = op(L, get(false, ran[root[u]].first, ran[u].first + 1));
                u = per[root[u]];
            } else {
                R = op(get(true, ran[root[v]].first, ran[v].first + 1), R);
                v = per[root[v]];
            }
        }
        if (ran[v].first < ran[u].first) {
            L = op(L, get(false, ran[v].first, ran[u].first + 1));
        } else {
            R = op(get(true, ran[u].first, ran[v].first + 1), R);
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
        return get(true, ran[u].first, ran[u].second + 1);
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
