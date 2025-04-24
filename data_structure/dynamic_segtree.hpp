#pragma once
#include <memory>

template <typename T, auto op, auto e, uint64_t n = 1000000000000000001LL>
struct DynamicSegtree {
    struct node;
    using nptr = std::unique_ptr<node>;
    struct node {
        int64_t p;
        T v, prod;
        nptr left, right;
        node(int64_t _p, T _v) : p(_p), v(_v), prod(_v), left(nullptr), right(nullptr) {}
        void update() {
            prod = op(op(left ? left->prod : e(), v), right ? right->prod : e());
        }
    };
    nptr root;
    DynamicSegtree() : root(nullptr) {}
    void set(int64_t p, T v) {
        set(root, 0, n, p, v);
    }
    void set(nptr& ptr, int64_t l, int64_t r, int64_t p, T v) {
        if (!ptr) {
            ptr = std::make_unique<node>(p, v);
            return;
        }
        if (ptr->p == p) {
            ptr->v = v;
            ptr->update();
            return;
        }
        int64_t mid = (l + r) >> 1;
        if (p < mid) {
            if (ptr->p < p) std::swap(ptr->p, p), std::swap(ptr->v, v);
            set(ptr->left, l, mid, p, v);
        } else {
            if (p < ptr->p) std::swap(ptr->p, p), std::swap(ptr->v, v);
            set(ptr->right, mid, r, p, v);
        }
        ptr->update();
    }
    T operator[](int64_t p) {
        return get(root, p, 0, n);
    }
    T get(const nptr& ptr, int64_t p, int64_t l, int64_t r) {
        if (!ptr) return e();
        if (ptr->p == p) return ptr->v;
        int64_t mid = (l + r) >> 1;
        if (p < mid) {
            return get(ptr->left, p, l, mid);
        } else {
            return get(ptr->right, p, mid, r);
        }
    }
    T operator()(int64_t L, int64_t R) {
        return prod(root, 0, n, L, R);
    }
    T prod(const nptr& ptr, int64_t l, int64_t r, int64_t L, int64_t R) {
        if (!ptr or r <= L or R <= l) return e();
        if (L <= l and r <= R) return ptr->prod;
        int64_t mid = (l + r) >> 1;
        T res = prod(ptr->left, l, mid, L, R);
        if (L <= ptr->p and ptr->p < R) res = op(res, ptr->v);
        return op(res, prod(ptr->right, mid, r, L, R));
    }

    int64_t max_right(int64_t L, const auto& f) {
        T sum = e();
        return max_right(root, 0, n, L, sum, f);
    }
    int64_t max_right(const nptr& ptr, int64_t l, int64_t r, int64_t L, T& sum, const auto& f) {
        if (!ptr or r <= L) return n;
        if (L <= l and f(op(sum, ptr->prod))) {
            sum = op(sum, ptr->prod);
            return n;
        }
        int64_t mid = (l + r) >> 1;
        if (ptr->p < L) {
            return max_right(ptr->right, mid, r, L, sum, f);
        }
        int64_t res = max_right(ptr->left, l, mid, L, sum, f);
        if (res != n) return res;
        sum = op(sum, ptr->v);
        if (!f(sum)) {
            return ptr->p;
        }
        return max_right(ptr->right, mid, r, L, sum, f);
    }

    int64_t min_left(int64_t R, const auto& f) {
        T sum = e();
        return min_left(root, 0, n, R, sum, f);
    }
    int64_t min_left(const nptr& ptr, int64_t l, int64_t r, int64_t R, T& sum, const auto& f) {
        if (!ptr or R <= l) return 0;
        if (r <= R and f(op(ptr->prod, sum))) {
            sum = op(ptr->prod, sum);
            return 0;
        }
        int64_t mid = (l + r) >> 1;
        if (R <= ptr->p) {
            return min_left(ptr->left, l, mid, R, sum, f);
        }
        int64_t res = min_left(ptr->right, mid, r, R, sum, f);
        if (res != 0) return res;
        sum = op(ptr->v, sum);
        if (!f(sum)) {
            return ptr->p + 1;
        }
        return min_left(ptr->left, l, mid, R, sum, f);
    }
};
