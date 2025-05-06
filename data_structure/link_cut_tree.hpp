#pragma once
#include <data_structure/splay_tree.hpp>
#include <vector>

template <typename T, auto op, auto e>
struct LinkCutTree {
    using Splay = SplayTree<T, op, e>;
    using nptr = Splay::nptr;
    Splay tree;
    std::vector<nptr> node;

    void add(T x) {
        node.emplace_back(new Splay::node{x});
    }

    void expose(nptr& ptr) {
        while (true) {
            tree.splay(ptr);
            ptr->right = nullptr;
            tree.update(ptr);
            if (!ptr->parent) {
                return;
            }
            tree.splay(ptr->parent);
            ptr->parent->right = ptr;
            tree.update(ptr->parent);
        }
    }

    void evert(nptr ptr) {
        expose(ptr);
        tree.toggle(ptr);
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
        tree.update(v);
    }

    void set(int U, T x) {
        nptr u = node[U];
        expose(u);
        u->v = x;
        tree.update(u);
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
};
