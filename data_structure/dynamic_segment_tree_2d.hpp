#pragma once
#include <data_structure/dynamic_segment_tree.hpp>
#include <math/point.hpp>

template <typename T, auto op, auto e, typename S = int64_t, S n = 1000000000000000001LL>
struct DynamicSegmentTree2D {
    struct node;
    using nptr = std::unique_ptr<node>;
    using seg = DynamicSegmentTree<T, op, e, S, n>;
    struct node {
        S x;
        seg v{}, prod{};
        nptr left{nullptr}, right{nullptr};
        node(S _x) : x(_x) {}
        void update(S y) {
            prod.set(y, op(op(left ? left->prod[y] : e(), v[y]), right ? right->prod[y] : e()));
        }
    };
    nptr root{nullptr};
    DynamicSegmentTree2D() {}

    void set(S x, S y, T v) {
        std::stack<nptr*> st;
        nptr* ptr = &root;
        seg sg{};
        sg.set(y, v);
        S l = 0, r = n;
        bool flg = true;
        while (*ptr) {
            st.emplace(ptr);
            nptr& cur = *ptr;
            S mid = (l + r) >> 1;
            if (cur->x == x) {
                cur->v.set(y, v);
                flg = false;
                break;
            }
            if (x < mid) {
                if (cur->x < x) {
                    std::swap(cur->x, x);
                    std::swap(cur->v, sg);
                }
                ptr = &cur->left;
                r = mid;
            } else {
                if (x < cur->x) {
                    std::swap(cur->x, x);
                    std::swap(cur->v, sg);
                }
                ptr = &cur->right;
                l = mid;
            }
        }
        if (flg) {
            *ptr = std::make_unique<node>(node{x});
            (*ptr)->v = std::copy(sg);
            (*ptr)->prod = std::move(sg);
        }
        while (!st.empty()) {
            st.top()->get()->update(y);
            st.pop();
        }
    }

    void set(Point<T> p, T v) {
        set(p.x, p.y, v);
    }

    void add(S x, S y, T v) {
        std::stack<nptr*> st;
        nptr* ptr = &root;
        seg sg{};
        sg.set(y, v);
        S l = 0, r = n;
        bool flg = true;
        while (*ptr) {
            st.emplace(ptr);
            nptr& cur = *ptr;
            S mid = (l + r) >> 1;
            if (cur->x == x) {
                cur->v.add(y, v);
                flg = false;
                break;
            }
            if (x < mid) {
                if (cur->x < x) {
                    std::swap(cur->x, x);
                    std::swap(cur->v, sg);
                }
                ptr = &cur->left;
                r = mid;
            } else {
                if (x < cur->x) {
                    std::swap(cur->x, x);
                    std::swap(cur->v, sg);
                }
                ptr = &cur->right;
                l = mid;
            }
        }
        if (flg) {
            *ptr = std::make_unique<node>(node{x});
            (*ptr)->v = std::copy(sg);
            (*ptr)->prod = std::move(sg);
        }
        while (!st.empty()) {
            st.top()->get()->update(y);
            st.pop();
        }
    }

    void add(Point<T> p, T v) {
        add(p.x, p.y, v);
    }

    T operator[](S x, S y) {
        nptr* ptr = &root;
        S l = 0, r = n;
        while (*ptr) {
            nptr& cur = *ptr;
            if (cur->x == x) {
                return cur->v[y];
            }
            S mid = (l + r) >> 1;
            if (x < mid) {
                ptr = &cur->left;
                r = mid;
            } else {
                ptr = &cur->right;
                l = mid;
            }
        }
        return e();
    }

    T operator()(S L, S D, S R, S U) {
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
                    res = op(res, ptr->prod(D, U));
                    continue;
                }
                S mid = (l + r) >> 1;
                st.emplace(ptr->right, mid, r, true);
                if (ptr->x >= L && ptr->x < R) {
                    st.emplace(ptr, l, r, false);
                }
                st.emplace(ptr->left, l, mid, true);
            } else {
                res = op(res, ptr->v(D, U));
            }
        }
        return res;
    }
};
