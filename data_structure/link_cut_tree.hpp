#pragma once
#include <cstdint>
#include <data_structure/splay_tree.hpp>
#include <vector>

template <typename T, auto op, auto e>
struct LinkCutTree : public SplayTree<T, op, e> {
    using Splay = SplayTree<T, op, e>;
    using nptr = Splay::nptr;
    std::vector<nptr> node;

    LinkCutTree() {}
    LinkCutTree(int n) {
        for (int i = 0; i < n; i++) {
            add(e());
        }
    }
    LinkCutTree(const std::vector<std::vector<int>>& g) : LinkCutTree(g, std::vector<T>(g.size(), e())) {}
    LinkCutTree(const std::vector<std::vector<int>>& g, const std::vector<T>& v) {
        for (uint32_t i = 0, siz = v.size(); i < siz; ++i) {
            add(v[i]);
        }
        for (int u = 0, siz = v.size(); u < siz; ++u) {
            for (int v : g[u]) {
                if (u > v) continue;
                link(u, v);
            }
        }
    }

    void add(T x) {
        node.emplace_back(new Splay::node{x, static_cast<int>(node.size())});
    }

    int expose(nptr& ptr) {
        nptr last = ptr;
        while (true) {
            Splay::splay(ptr);
            ptr->right = nullptr;
            Splay::update(ptr);
            if (!ptr->parent) {
                return last->idx;
            }
            last = ptr->parent;
            Splay::splay(ptr->parent);
            ptr->parent->right = ptr;
            Splay::update(ptr->parent);
        }
    }

    void evert(nptr ptr) {
        expose(ptr);
        Splay::toggle(ptr);
    }

    void link(int U, int V) {
        nptr u = node[U];
        nptr v = node[V];
        evert(v);
        v->parent = u;
    }

    void cut(int U, int V) {
        nptr u = node[U];
        nptr v = node[V];
        evert(u);
        expose(v);
        v->left->parent = nullptr;
        v->left = nullptr;
        Splay::update(v);
    }

    void set(int U, T x) {
        nptr u = node[U];
        expose(u);
        u->v = x;
        Splay::update(u);
    }

    T operator[](int U) {
        nptr u = node[U];
        expose(u);
        return u->v;
    }

    T operator()(int U, int V) {
        nptr u = node[U];
        nptr v = node[V];
        evert(u);
        expose(v);
        return v->p;
    }

    int lca(int U, int V) {
        nptr u = node[U];
        nptr v = node[V];
        expose(u);
        return expose(v);
    }
};
