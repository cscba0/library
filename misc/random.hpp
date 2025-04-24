#pragma once
#include <data_structure/unionfind.hpp>
#include <random>
#include <templates/rep.hpp>

template <typename T>
T rnd(T l, T r) {
    std::uniform_int_distribution<T> x(l, r);
    std::mt19937 mt(std::random_device{}());
    return x(mt);
}

template <typename T>
T rnd(T r) {
    return rnd((T)1, r);
}

inline std::string rnd_str(int n = 1, char l = 'a', char r = 'z') {
    std::string res = "";
    rep(_, n) {
        res += (char)rnd(l, r);
    }
    return res;
}

template <typename T>
std::vector<T> rnd_vec(int n, T l, T r) {
    std::vector<T> res;
    rep(i, n) {
        res.emplace_back(rnd(l, r));
    }
    return res;
}

template <typename T>
std::vector<T> rnd_vec(int n, T r) {
    std::vector<T> res;
    rep(i, n) {
        res.emplace_back(rnd(r));
    }
    return res;
}

inline std::vector<std::pair<int, int>> rnd_tree(int n) {
    std::vector<std::pair<int, int>> res;
    Unionfind uf(n + 1);
    rep(_, n - 1) {
        int u, v;
        do {
            u = rnd(n), v = rnd(n);
        } while (uf.same(u, v));
        res.emplace_back(std::make_pair(std::min(u, v), std::max(u, v)));
        uf.merge(u, v);
    }
    return res;
}
