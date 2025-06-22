#pragma once
#include <vector>

template <typename T,
          typename S,
          auto vertex,
          auto compress,
          auto rake,
          auto addedge,
          auto addvertex>
struct StaticTopTree {
    enum Type {
        Vertex,
        Compress,
        Rake,
        AddEdge,
        AddVertex
    };
    std::vector<T> v, point;
    std::vector<S> path;
    std::vector<std::vector<int>>& g;
    int root;
    std::vector<int> p, l, r;
    std::vector<Type> t;
    int n;

    StaticTopTree(std::vector<std::vector<int>>& _g, const std::vector<T>& _v) : v(_v), g(_g), n(_g.size()) {
        point.resize(g.size() * 4Z);
        path.resize(g.size() * 4Z);
        p.resize(g.size() * 4Z);
        l.resize(g.size() * 4Z);
        r.resize(g.size() * 4Z);
        t.resize(g.size() * 4Z, Type::Vertex);
        build();
    }

    int dfs(int u) {
        int sum = 1, cur = 0;
        for (int& v_ref : g[u]) {
            int c = dfs(v_ref);
            sum += c;
            if (cur < c) {
                cur = c;
                std::swap(v_ref, g[u][0]);
            }
        }
        return sum;
    }

    int add(int u, int _l, int _r, Type _t) {
        if (u == -1) {
            u = n++;
        }
        p[u] = -1;
        l[u] = _l;
        r[u] = _r;
        t[u] = _t;
        if (_l != -1) {
            p[_l] = u;
        }
        if (_r != -1) {
            p[_r] = u;
        }
        return u;
    }

    std::pair<int, int> merge(const std::vector<std::pair<int, int>>& vec, Type _t) {
        if (vec.size() == 1Z) {
            return vec[0];
        }
        int sum = 0;
        for (auto [_, s] : vec) {
            sum += s;
        }
        std::vector<std::pair<int, int>> lc, rc;
        for (auto [v, s] : vec) {
            if (s < sum) {
                lc.emplace_back(v, s);
            } else {
                rc.emplace_back(v, s);
            }
            sum -= s * 2;
        }
        auto [_l, ls] = merge(lc, _t);
        auto [_r, rs] = merge(rc, _t);
        return {add(-1, _l, _r, _t), ls + rs};
    }

    std::pair<int, int> _compress(int u) {
        std::vector<std::pair<int, int>> c{_addvertex(u)};
        while (!g[u].empty()) {
            c.emplace_back(_addvertex(g[u][0]));
            u = g[u][0];
        }
        return merge(c, Type::Compress);
    }

    std::pair<int, int> _rake(int u) {
        std::vector<std::pair<int, int>> c;
        for (int i = 1; i < int(g[u].size()); ++i) {
            c.emplace_back(_addedge(g[u][i]));
        }
        if (c.empty()) {
            return std::pair<int, int>{-1, 0};
        }
        return merge(c, Type::Rake);
    }

    std::pair<int, int> _addedge(int u) {
        auto [v, s] = _compress(u);
        return {add(-1, v, -1, Type::AddEdge), s};
    }

    std::pair<int, int> _addvertex(int u) {
        auto [v, s] = _rake(u);
        return {add(u, v, -1, v == -1 ? Type::Vertex : Type::AddVertex), s + 1};
    }

    void build() {
        dfs(0);
        root = _compress(0).first;
        auto f = [&](auto f, int u) -> void {
            if (l[u] != -1) {
                f(f, l[u]);
            }
            if (r[u] != -1) {
                f(f, r[u]);
            }
            _update(u);
        };
        f(f, root);
    }

    void _update(int u) {
        if (t[u] == Type::Vertex) {
            path[u] = vertex(v[u]);
        } else if (t[u] == Type::Compress) {
            path[u] = compress(path[l[u]], path[r[u]]);
        } else if (t[u] == Type::Rake) {
            point[u] = rake(point[l[u]], point[r[u]]);
        } else if (t[u] == Type::AddEdge) {
            point[u] = addedge(path[l[u]]);
        } else if (t[u] == Type::AddVertex) {
            path[u] = addvertex(point[l[u]], v[u]);
        }
    }

    void set(int u, T x) {
        v[u] = x;
        while (u != -1) {
            _update(u);
            u = p[u];
        }
    }
};
