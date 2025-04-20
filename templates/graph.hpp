#pragma once
#include <vector>

#define OVERLOAD_GRAPH(_1, _2, _3, name, ...) name
#define GRAPH1(g) GRAPH3(g, n, m);
#define GRAPH2(g, m) GRAPH3(g, n, m);
#define GRAPH3(g, n, m)           \
    vector<vector<int>> g(n);     \
    for (int i = 0; i < m; i++) { \
        int u, v;                 \
        cin >> u >> v;            \
        u--;                      \
        v--;                      \
        g[u].emplace_back(v);     \
        g[v].emplace_back(u);     \
    }
#define graph(...) OVERLOAD_GRAPH(__VA_ARGS__, GRAPH3, GRAPH2, GRAPH1)(__VA_ARGS__)
using graph = std::vector<std::vector<int>>;
#define OVERLOAD_DGRAPH(_1, _2, _3, name, ...) name
#define DGRAPH1(g) DGRAPH3(g, n, m);
#define DGRAPH2(g, m) DGRAPH3(g, n, m);
#define DGRAPH3(g, n, m)          \
    vector<vector<int>> g(n);     \
    for (int i = 0; i < m; i++) { \
        int u, v;                 \
        cin >> u >> v;            \
        u--;                      \
        v--;                      \
        g[u].emplace_back(v);     \
    }
#define dgraph(...) OVERLOAD_DGRAPH(__VA_ARGS__, DGRAPH3, DGRAPH2, DGRAPH1)(__VA_ARGS__)
