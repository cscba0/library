#pragma once
#include <data_structure/randomized_binary_search_tree.hpp>

template <typename T, auto op, auto e, typename S, auto mapping, auto composition, auto id>
struct LazyReversibleRandomizedBinarySearchTree {
    struct node;
    using nptr = std::unique_ptr<node>;
    struct node {
        T v, r, p;
        S lz{id()};
        bool rev{false};
        int siz{1};
        nptr left{nullptr}, right{nullptr};
        node(T _v) : v(_v), r(_v), p(_v) {}
    };

    void update(nptr& ptr) {
        ptr->siz = size(ptr->left) + size(ptr->right) + 1;
        ptr->p = op(op(ptr->left ? ptr->left->p : e(), ptr->v), ptr->right ? ptr->right->p : e());
        ptr->r = op(op(ptr->right ? ptr->right->p : e(), ptr->v), ptr->left ? ptr->left->p : e());
    }

    static int size(const nptr& ptr) {
        return !ptr ? 0 : ptr->siz;
    }

    void push(nptr& ptr) {
        if (ptr->rev) {
            if (ptr->left) {
                toggle(ptr->left);
            }
            if (ptr->right) {
                toggle(ptr->right);
            }
            ptr->rev = false;
        }
        {
            if (ptr->left) {
                prop(ptr->left, ptr->lz);
            }
            if (ptr->right) {
                prop(ptr->right, ptr->lz);
            }
            ptr->lz = id();
        }
    }

    void toggle(nptr& ptr) {
        if (!ptr) {
            return;
        }
        std::swap(ptr->left, ptr->right);
        std::swap(ptr->p, ptr->r);
        ptr->rev ^= true;
    }

    void prop(nptr& ptr, const S x) {
        if (!ptr) return;
        ptr->v = mapping(x, ptr->v);
        ptr->p = mapping(x, ptr->p);
        ptr->r = mapping(x, ptr->r);
        ptr->lz = composition(x, ptr->lz);
    }

    static inline int rng() {
        static int x = 123456789;
        static int y = 362436069;
        static int z = 521288629;
        static int w = 88675123;
        int t;
        t = x ^ (x << 11);
        x = y;
        y = z;
        z = w;
        return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
    }

    nptr merge(nptr l, nptr r) {
        if (!l || !r) return l ? std::move(l) : std::move(r);
        if (rng() % (size(l) + size(r)) < size(l)) {
            push(l);
            l->right = merge(std::move(l->right), std::move(r));
            update(l);
            return std::move(l);
        } else {
            push(r);
            r->left = merge(std::move(l), std::move(r->left));
            update(r);
            return std::move(r);
        }
    }

    std::pair<nptr, nptr> split(nptr ptr, int k) {
        if (!ptr) {
            return {nullptr, nullptr};
        }
        push(ptr);
        if (k <= size(ptr->left)) {
            auto [L, R] = split(std::move(ptr->left), k);
            ptr->left = std::move(R);
            update(ptr);
            return {std::move(L), std::move(ptr)};
        } else {
            auto [L, R] = split(std::move(ptr->right), k - size(ptr->left) - 1);
            ptr->right = std::move(L);
            update(ptr);
            return {std::move(ptr), std::move(R)};
        }
    }

    void insert(nptr& ptr, int k, T v) {
        auto [L, R] = split(std::move(ptr), k);
        nptr new_ptr = std::make_unique<node>(v);
        ptr = merge(merge(std::move(L), std::move(new_ptr)), std::move(R));
    }

    void erase(nptr& ptr, int k) {
        auto [L, tmp] = split(std::move(ptr), k);
        auto [M, R] = split(std::move(tmp), 1);
        M.reset();
        ptr = merge(std::move(L), std::move(R));
    }

    void reverse(nptr& ptr, int l, int r) {
        auto [L, tmp] = split(std::move(ptr), l);
        auto [M, R] = split(std::move(tmp), r - l);
        toggle(M);
        ptr = merge(merge(std::move(L), std::move(M)), std::move(R));
    }

    void apply(nptr& ptr, int l, int r, S x) {
        auto [L, tmp] = split(std::move(ptr), l);
        auto [M, R] = split(std::move(tmp), r - l);
        prop(M, x);
        ptr = merge(merge(std::move(L), std::move(M)), std::move(R));
    }

    T operator()(nptr& ptr, int l, int r) {
        auto [L, tmp] = split(std::move(ptr), l);
        auto [M, R] = split(std::move(tmp), r - l);
        auto res = M ? M->p : e();
        ptr = merge(merge(std::move(L), std::move(M)), std::move(R));
        return res;
    }
};
