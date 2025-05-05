#pragma once

#include <utility>

template <typename T, auto op, auto e, typename S, auto mapping, auto composition, auto id>
struct LazyReversibleSplayTree {
    struct node;
    using nptr = node*;
    struct node {
        T v, p, r;
        S lz{id()};
        bool rev{false};
        int siz{1};
        nptr left{nullptr}, right{nullptr}, parent{nullptr};
        node(T _v) : v(_v), p(_v), r(_v) {}
    };

    void update(nptr ptr) {
        ptr->siz = size(ptr->left) + size(ptr->right) + 1;
        ptr->p = op(op(ptr->left ? ptr->left->p : e(), ptr->v), ptr->right ? ptr->right->p : e());
        ptr->r = op(op(ptr->right ? ptr->right->r : e(), ptr->v), ptr->left ? ptr->left->r : e());
    }

    static int size(const nptr ptr) {
        return !ptr ? 0 : ptr->siz;
    }

    static bool is_root(const nptr ptr) {
        return !ptr->parent || (ptr->parent->left != ptr && ptr->parent->right != ptr);
    }

    void push(nptr ptr) {
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

    void toggle(nptr ptr) {
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

    void splay(nptr ptr) {
        if (!ptr) return;
        push(ptr);
        while (!is_root(ptr)) {
            nptr x = ptr->parent;
            if (is_root(x)) {
                push(x);
                push(ptr);
                rotate(ptr);
            } else {
                nptr y = x->parent;
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

    nptr get_left(nptr ptr) {
        while (ptr->left) {
            push(ptr);
            ptr = ptr->left;
        }
        return ptr;
    }

    nptr get_right(nptr ptr) {
        while (ptr->right) {
            push(ptr);
            ptr = ptr->right;
        }
        return ptr;
    }

    nptr merge(nptr l, nptr r) {
        if (!l && !r) {
            return nullptr;
        }
        if (!l) {
            return r;
        }
        if (!r) {
            return l;
        }
        l = get_right(l);
        splay(l);
        l->right = r;
        l->right->parent = l;
        update(l);
        return l;
    }
    std::pair<nptr, nptr> split(nptr ptr, int k) {
        if (!ptr) {
            return {nullptr, nullptr};
        }
        if (k == 0) {
            ptr->parent = nullptr;
            return {nullptr, ptr};
        }
        if (k == size(ptr)) {
            ptr->parent = nullptr;
            return {ptr, nullptr};
        }
        push(ptr);
        if (k <= size(ptr->left)) {
            auto [L, R] = split(ptr->left, k);
            ptr->left = R;
            ptr->parent = nullptr;
            if (R) {
                R->parent = ptr;
            }
            update(ptr);
            return {L, ptr};
        } else {
            auto [L, R] = split(ptr->right, k - size(ptr->left) - 1);
            ptr->right = L;
            ptr->parent = nullptr;
            if (L) {
                L->parent = ptr;
            }
            update(ptr);
            return {ptr, R};
        }
    }

    inline int pos(const nptr ptr) {
        if (ptr->parent) {
            if (ptr->parent->left == ptr) return -1;
            if (ptr->parent->right == ptr) return 1;
        }
        return 0;
    }

    void rotate(nptr ptr) {
        nptr x = ptr->parent;
        nptr y = x->parent;
        if (pos(ptr) == -1) {
            if ((x->left = ptr->right)) {
                x->left->parent = x;
            }
            ptr->right = x;
            x->parent = ptr;
        } else {
            if ((x->right = ptr->left)) {
                x->right->parent = x;
            }
            ptr->left = x;
            x->parent = ptr;
        }
        update(x);
        update(ptr);
        if ((ptr->parent = y)) {
            if (y->left == x) {
                y->left = ptr;
            }
            if (y->right == x) {
                y->right = ptr;
            }
        }
    }

    void insert(nptr& ptr, int k, T v) {
        splay(ptr);
        auto [L, R] = split(ptr, k);
        nptr new_ptr = new node{v};
        ptr = merge(merge(L, new_ptr), R);
    }

    void erase(nptr& ptr, int k) {
        splay(ptr);
        auto [L, tmp] = split(ptr, k);
        auto [M, R] = split(tmp, 1);
        delete M;
        ptr = merge(L, R);
    }

    void reverse(nptr& ptr, int l, int r) {
        auto [L, tmp] = split(ptr, l);
        auto [M, R] = split(tmp, r - l);
        toggle(M);
        ptr = merge(merge(L, M), R);
    }

    void apply(nptr& ptr, int l, int r, S x) {
        auto [L, tmp] = split(ptr, l);
        auto [M, R] = split(tmp, r - l);
        prop(M, x);
        ptr = merge(merge(L, M), R);
    }

    T operator()(nptr& ptr, int l, int r) {
        auto [L, tmp] = split(ptr, l);
        auto [M, R] = split(tmp, r - l);
        auto res = M ? M->p : e();
        ptr = merge(merge(L, M), R);
        return res;
    }
};
