#pragma once
#include <utility>

template <typename T, auto op, auto e>
struct SplayTree {
    struct node;
    using nptr = node*;
    struct node {
        T v, p, r;
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

    void splay(nptr& ptr, int root_size) {
        if (!ptr) return;
        push(ptr);
        while (ptr->siz != root_size) {
            nptr p = ptr->parent, pp = ptr->parent;
            if (p->siz == root_size) {
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
        int root_size = ptr->siz;
        while (true) {
            if (!ptr) return nullptr;
            push(ptr);
            int siz = size(ptr->left);
            if (k < siz) {
                ptr = ptr->left;
            } else if (k == siz) {
                splay(ptr, root_size);
                return ptr;
            } else {
                k -= siz + 1;
                ptr = ptr->right;
            }
        }
    }

    inline int pos(const nptr& ptr) {
        if (ptr->parent) {
            if (ptr->parent->left == ptr) return -1;
            if (ptr->parent->right == ptr) return 1;
        }
        return 0;
    }

    void rotate(nptr& ptr) {
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
        nptr new_ptr = new node{v};
        if (!ptr) {
            ptr = new_ptr;
            return;
        }
        if (ptr->siz == k) {
            new_ptr->left = ptr;
            ptr->parent = new_ptr;
            ptr = new_ptr;
            update(ptr);
        } else if (k == 0) {
            new_ptr->right = ptr;
            ptr->parent = new_ptr;
            ptr = new_ptr;
            update(ptr);
        } else {
            ptr = kth(ptr, k);
            new_ptr->left = ptr->left;
            ptr->left->parent = new_ptr;
            new_ptr->right = ptr;
            ptr->parent = new_ptr;
            ptr->left = nullptr;
            update(ptr);
            ptr = new_ptr;
            update(ptr);
        }
    }

    void erase(nptr& ptr, int k) {
        ptr = kth(ptr, k);
        nptr l = ptr->left, r = ptr->right;
        delete ptr;
        ptr = merge(l, r);
    }

    void reverse(nptr& ptr, int l, int r) {
        if (r <= l) return;
        if (l == 0 && r == ptr->siz) {
            toggle(ptr);
        } else if (l == 0) {
            ptr = kth(ptr, r);
            toggle(ptr->left);
            update(ptr);
        } else if (r == ptr->siz) {
            ptr = kth(ptr, l - 1);
            toggle(ptr->right);
            update(ptr);
        } else {
            ptr = kth(ptr, l - 1);
            ptr->right = kth(ptr->right, r - l);
            toggle(ptr->right->left);
            update(ptr->right);
            update(ptr);
        }
    }

    T operator()(nptr& ptr, int l, int r) {
        if (r <= l) return e();
        if (l == 0 && r == ptr->siz) {
            return ptr->p;
        } else if (l == 0) {
            ptr = kth(ptr, r);
            return ptr->left->p;
        } else if (r == ptr->siz) {
            ptr = kth(ptr, l - 1);
            return ptr->right->p;
        } else {
            ptr = kth(ptr, l - 1);
            ptr->right = kth(ptr->right, r - l);
            return ptr->right->left->p;
        }
    }
};
