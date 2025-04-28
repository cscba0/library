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
            st.emplace(ptr);
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
            st.emplace(ptr);
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

    T operator()(S L, S R) {
        if (!root) return e();
        T res = e();
        std::stack<std::tuple<const nptr&, S, S, bool>> st;
        st.emplace(root, 0, n, true);
        while (!st.empty()) {
            auto [ptr, l, r, flg] = st.top();
            st.pop();
            if (flg) {
                if (!ptr || r <= L || R <= l) continue;
                if (L <= l && r <= R) {
                    res = op(res, ptr->prod);
                    continue;
                }
                S mid = (l + r) >> 1;
                st.emplace(ptr->right, mid, r, true);
                if (ptr->p >= L && ptr->p < R) {
                    st.emplace(ptr, l, r, false);
                }
                st.emplace(ptr->left, l, mid, true);
            } else {
                res = op(res, ptr->v);
            }
        }
        return res;
    }

    S max_right(S L, const auto& f) {
        T sum = e();
        std::stack<std::tuple<const nptr&, S, S, bool>> st;
        st.emplace(root, 0, n, true);
        while (!st.empty()) {
            auto [ptr, l, r, flg] = st.top();
            st.pop();
            S mid = (l + r) >> 1;
            if (flg) {
                if (!ptr || r <= L) continue;
                if (L <= l && f(op(sum, ptr->prod))) {
                    sum = op(sum, ptr->prod);
                    continue;
                }
                if (ptr->p < L) {
                    st.emplace(ptr->right, mid, r, true);
                } else {
                    st.emplace(ptr, l, r, false);
                    st.emplace(ptr->left, l, mid, true);
                }
            } else {
                sum = op(sum, ptr->v);
                if (!f(sum)) {
                    return ptr->p;
                }
                st.emplace(ptr->right, mid, r, true);
            }
        }
        return n;
    }

    S min_left(S R, const auto& f) {
        T sum = e();
        std::stack<std::tuple<const nptr&, S, S, bool>> st;
        st.emplace(root, 0, n, true);
        while (!st.empty()) {
            auto [ptr, l, r, first] = st.top();
            st.pop();
            if (!ptr || R <= l) continue;
            S mid = (l + r) >> 1;
            if (first) {
                if (r <= R && f(op(ptr->prod, sum))) {
                    sum = op(ptr->prod, sum);
                    continue;
                }
                if (R <= ptr->p) {
                    st.emplace(ptr->left, l, mid, true);
                } else {
                    st.emplace(ptr, l, r, false);
                    st.emplace(ptr->right, mid, r, true);
                }
            } else {
                sum = op(ptr->v, sum);
                if (!f(sum)) {
                    return ptr->p + 1;
                }
                st.emplace(ptr->left, l, mid, true);
            }
        }
        return 0;
    }
};
