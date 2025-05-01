#pragma once
#include <memory>
#include <stack>

template <typename T, T Left, T Right, auto e>
struct DynamicLiChaoTree {
    struct node;
    using nptr = std::unique_ptr<node>;
    struct node {
        T a, b;
        nptr left{nullptr}, right{nullptr};
        node(T _a, T _b) : a(_a), b(_b) {}
        T get(T x) {
            return x * a + b;
        }
    };
    nptr root{nullptr};
    DynamicLiChaoTree() {}

    void add(T a, T b, nptr* ptr = nullptr, T l = Left, T r = Right) {
        if (!ptr) {
            ptr = &root;
        }
        while (*ptr) {
            nptr& cur = *ptr;
            T mid = (l + r) >> 1;
            T L = a * l + b;
            T M = a * mid + b;
            T R = a * (r - 1) + b;
            T cL = cur->get(l);
            T cM = cur->get(mid);
            T cR = cur->get(r - 1);
            if (cL <= L && cR <= R) {
                return;
            }
            if (L <= cL && R <= cR) {
                std::swap(cur->a, a);
                std::swap(cur->b, b);
                return;
            }
            if (L <= cL) {
                if (M <= cM) {
                    std::swap(cur->a, a);
                    std::swap(cur->b, b);
                    ptr = &cur->right;
                    l = mid;
                } else {
                    ptr = &cur->left;
                    r = mid;
                }
            } else {
                if (M <= cM) {
                    std::swap(cur->a, a);
                    std::swap(cur->b, b);
                    ptr = &cur->left;
                    r = mid;
                } else {
                    ptr = &cur->right;
                    l = mid;
                }
            }
            if (r <= l + 1) return;
        }
        if (*ptr) {
            if (a * l + b <= (*ptr)->get(l)) {
                std::swap((*ptr)->a, a);
                std::swap((*ptr)->b, b);
            }
        } else {
            *ptr = std::make_unique<node>(a, b);
        }
    }

    void add(T a, T b, T L, T R) {
        std::stack<std::tuple<nptr*, T, T>> st;
        st.emplace(&root, Left, Right);
        while (!st.empty()) {
            auto [ptr, l, r] = st.top();
            st.pop();
            if (r <= L || R <= l) continue;
            if (L <= l && r <= R) {
                add(a, b, ptr, l, r);
                continue;
            }
            if (!*ptr) {
                *ptr = std::make_unique<node>(T{0}, e());
            }
            T mid = (l + r) >> 1;
            st.emplace(&((*ptr)->left), l, mid);
            st.emplace(&((*ptr)->right), mid, r);
        }
    }

    T operator()(T x) {
        T res{e()};
        nptr* ptr = &root;
        T l{Left}, r{Right};
        while (*ptr) {
            nptr& cur = *ptr;
            res = std::min(res, cur->get(x));
            T mid = (l + r) >> 1;
            if (x < mid) {
                ptr = &cur->left;
                r = mid;
            } else {
                ptr = &cur->right;
                l = mid;
            }
        }
        return res;
    }
};
