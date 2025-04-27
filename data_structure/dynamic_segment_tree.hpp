#pragma once
#include <memory>
#include <stack>

template <typename T, auto op, auto e, typename S = int64_t, S n = 1000000000000000001LL>
struct DynamicSegmentTree {
    struct node;
    using nptr = std::unique_ptr<node>;
    struct node {
        S p;
        T v, prod;
        nptr left, right;
        node(S _p, T _v) : p(_p), v(_v), prod(_v), left(nullptr), right(nullptr) {}
        void update() {
            prod = op(op(left ? left->prod : e(), v), right ? right->prod : e());
        }
    };
    nptr root{nullptr};
    DynamicSegmentTree() {}

    void set(S p, T v) {
        std::stack<nptr*> st;
        nptr* ptr = &root;
        S l = 0, r = n;
        bool flg = true;
        while (*ptr) {
            st.push(ptr);
            nptr& cur = *ptr;
            S mid = (l + r) >> 1;
            if (cur->p == p) {
                cur->v = v;
                flg = false;
                break;
            }
            if (p < mid) {
                if (cur->p < p) {
                    std::swap(cur->p, p);
                    std::swap(cur->v, v);
                }
                ptr = &cur->left;
                r = mid;
            } else {
                if (p < cur->p) {
                    std::swap(cur->p, p);
                    std::swap(cur->v, v);
                }
                ptr = &cur->right;
                l = mid;
            }
        }
        if (flg) {
            *ptr = std::make_unique<node>(p, v);
        }
        while (!st.empty()) {
            st.top()->get()->update();
            st.pop();
        }
    }

    void add(S p, T v) {
        std::stack<nptr*> st;
        nptr* ptr = &root;
        S l = 0, r = n;
        bool flg = true;
        while (*ptr) {
            st.push(ptr);
            nptr& cur = *ptr;
            S mid = (l + r) >> 1;
            if (cur->p == p) {
                cur->v += v;
                flg = false;
                break;
            }
            if (p < mid) {
                if (cur->p < p) {
                    std::swap(cur->p, p);
                    std::swap(cur->v, v);
                }
                ptr = &cur->left;
                r = mid;
            } else {
                if (p < cur->p) {
                    std::swap(cur->p, p);
                    std::swap(cur->v, v);
                }
                ptr = &cur->right;
                l = mid;
            }
        }
        if (flg) {
            *ptr = std::make_unique<node>(p, v);
        }
        while (!st.empty()) {
            st.top()->get()->update();
            st.pop();
        }
    }

    T operator[](S p) {
        nptr* ptr = &root;
        S l = 0, r = n;
        while (*ptr) {
            nptr& cur = *ptr;
            if (cur->p == p) {
                return cur->v;
            }
            S mid = (l + r) >> 1;
            if (p < mid) {
                ptr = &cur->left;
                r = mid;
            } else {
                ptr = &cur->right;
                l = mid;
            }
        }
        return e();
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
