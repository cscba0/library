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
            nptr p = ptr->parent, pp = ptr->parent;
            if (is_root(p)) {
                rotate(ptr);
                update(p);
            } else {
                if (pos(ptr) == pos(p)) {
                    rotate(p);
                    rotate(ptr);
                } else {
                    rotate(ptr);
                    rotate(ptr);
                }
            }
            update(p);
            update(pp);
        }
        update(ptr);
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
        if (!l) {
            return r;
        }
        if (!r) {
            return l;
        }
        l = kth(l, l->siz - 1);
        update(l);
        l->right = r;
        r->parent = l;
        update(l);
        return l;
    }

    nptr kth(nptr ptr, int k) {
        while (true) {
            push(ptr);
            int siz = size(ptr->left);
            if (k < siz) {
                ptr = ptr->left;
            } else if (k == siz) {
                splay(ptr);
                return ptr;
            } else {
                k -= siz + 1;
                ptr = ptr->right;
            }
        }
    }

    std::pair<nptr, nptr> split(nptr ptr, int k) {
        if (!ptr) return {nullptr, nullptr};
        if (k == 0) return {nullptr, ptr};
        if (k == ptr->siz) return {ptr, nullptr};
        ptr = kth(ptr, k);
        nptr l = ptr->left;
        ptr->left = nullptr;
        l->parent = nullptr;
        update(ptr);
        return {l, ptr};
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
        auto [L, R] = split(ptr, k);
        nptr new_ptr = new node{v};
        ptr = merge(merge(L, new_ptr), R);
    }

    void erase(nptr& ptr, int k) {
        ptr = kth(ptr, k);
        nptr l = ptr->left, r = ptr->right;
        if (l) {
            l->parent = nullptr;
        }
        if (r) {
            r->parent = nullptr;
        }
        delete ptr;
        ptr = merge(l, r);
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
