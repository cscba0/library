#pragma once
#include <memory>

template <typename T, auto op, auto e>
struct SplayTree {
    struct node;
    using nptr = std::unique_ptr<node>;
    struct node {
        T v, p, r;
        bool rev{false};
        int siz{1};
        nptr left{nullptr}, right{nullptr}, parent{nullptr};
        node(T _v) : v(_v), p(_v), r(_v) {}
    };

    void update(nptr& ptr) {
        ptr->siz = size(ptr->left) + size(ptr->right) + 1;
        ptr->p = op(op(ptr->left ? ptr->left->p : e(), ptr->v), ptr->right ? ptr->right->p : e());
        ptr->r = op(op(ptr->right ? ptr->right->p : e(), ptr->v), ptr->left ? ptr->left->p : e());
    }

    static int size(const nptr& ptr) {
        return !ptr ? 0 : ptr->siz;
    }

    static bool is_root(const nptr& ptr) {
        return !ptr->parent || (ptr->parent->left != ptr && ptr->parent->right != ptr);
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
    }

    void toggle(nptr& ptr) {
        if (!ptr) {
            return;
        }
        std::swap(ptr->left, ptr->right);
        std::swap(ptr->p, ptr->r);
        ptr->rev ^= true;
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

    void splay(nptr& ptr) {
        if (!ptr) return;
        push(ptr);
        while (!is_root(ptr)) {
            nptr& x = ptr->parent;
            if (is_root(x)) {
                push(x);
                push(ptr);
                rotate(ptr);
            } else {
                nptr& y = x->parent;
                push(y);
                push(x);
                push(ptr);
                if (pos(x) == pos(ptr)) {
                    rotate(x);
                    rotate(ptr);
                } else {
                    rotate(ptr);
                    rotate(ptr);
                }
            }
        }
    }

    nptr get_left(nptr& ptr) {
        while (ptr->left) {
            push(ptr);
            ptr = ptr->left;
        }
        return std::move(ptr);
    }

    nptr get_right(nptr& ptr) {
        while (ptr->right) {
            push(ptr);
            ptr = ptr->right;
        }
        return std::move(ptr);
    }

    nptr merge(nptr l, nptr r) {
        if (!l && !r) {
            return nullptr;
        }
        if (!l) {
            splay(r);
            return std::move(r);
        }
        if (!r) {
            splay(l);
            return std::move(l);
        }
        splay(l);
        splay(r);
        l = get_right(l);
        splay(l);
        l->right = std::move(r);
        l->right->parent = l.get();
        update(l);
        return std::move(l);
    }

    std::pair<nptr, nptr> split(nptr ptr, int k) {
        if (!ptr) {
            return {nullptr, nullptr};
        }
        if (k == 0) {
            return {nullptr, std::move(ptr)};
        }
        if (k == size(ptr)) {
            return {std::move(ptr), nullptr};
        }
        push(ptr);
        if (k <= size(ptr->left)) {
            auto [L, R] = split(std::move(ptr->left), k);
            ptr->left = std::move(R);
            if (ptr->left) {
                ptr->left->parent = ptr.get();
            }
            update(ptr);
            return {std::move(L), std::move(ptr)};
        } else {
            auto [L, R] = split(std::move(ptr->right), k - size(ptr->left) - 1);
            ptr->right = std::move(L);
            if (ptr->right) {
                ptr->right->parent = ptr.get();
            }
            update(ptr);
            return {std::move(ptr), std::move(R)};
        }
    }

    inline int pos(const nptr& ptr) {
        if (ptr->parent) {
            if (ptr->parent->left.get() == ptr.get()) return -1;
            if (ptr->parent->right.get() == ptr.get()) return 1;
        }
        return 0;
    }

    void rotate(nptr& ptr) {
        nptr x = std::move(ptr->parent);
        nptr y = std::move(x->parent);
        if (pos(ptr) == -1) {
            x->left = std::move(ptr->right);
            if (x->left) {
                x->left->parent = &x;
            }
            //     // ptr->right = std::move(x);
            //     // ptr->right->parent = ptr.get();
        } else {
            //     // if ((x->right = std::move(ptr->left))) {
            //     //     x->right->parent = x.get();
            //     // }
            //     // ptr->left = std::move(x);
            //     // ptr->left->parent = ptr.get();
        }
        // update(ptr->left);
        // update(ptr);
        // if ((ptr->parent = std::move(y))) {
        //     if (ptr->parent->left.get() == ptr->right.get()) {
        //         ptr->parent->left = std::move(ptr);
        //     }
        //     if (ptr->parent->right.get() == ptr->left.get()) {
        //         ptr->parent->right = std::move(ptr);
        //     }
        // }
    }

    void insert(nptr& ptr, int k, T v) {
        splay(ptr);
        // auto [L, R] = split(std::move(ptr), k);
        // nptr new_ptr = std::make_unique<node>(v);
        // ptr = merge(merge(std::move(L), std::move(new_ptr)), std::move(R));
    }

    void erase(nptr& ptr, int k) {
        splay(ptr);
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

    T operator()(nptr& ptr, int l, int r) {
        auto [L, tmp] = split(std::move(ptr), l);
        auto [M, R] = split(std::move(tmp), r - l);
        auto res = M ? M->p : e();
        ptr = merge(merge(std::move(L), std::move(M)), std::move(R));
        return res;
    }
};
