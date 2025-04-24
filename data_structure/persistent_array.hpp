#pragma once
#include <array>
#include <memory>
#include <vector>

template <typename T, auto e = []() { return T(); }>
struct PersistentArray {
    struct node;
    using nptr = std::shared_ptr<node>;
    struct node {
        T v{e()};
        std::array<nptr, 16> c;
        node() {}
        node(T _v) : v(_v) {}
    };
    std::vector<nptr> root;
    int w{0};
    PersistentArray(int n) : PersistentArray(std::vector<T>(n, e())) {}
    PersistentArray(int n, T x) : PersistentArray(std::vector<T>(n, x)) {}
    PersistentArray(std::vector<T> v) : root(1, std::make_shared<node>(node{})) {
        if (v.size() == 1U) {
            root[0] = std::make_shared<node>(node{v[0]});
            return;
        }
        std::vector<nptr> c;
        c.emplace_back(root[0]);
        while (1 << (w + 4) < v.size()) {
            w += 4;
            std::vector<nptr> nxt;
            for (auto &p : c) {
                for (int i = 0; i < 16; ++i) {
                    p->c[i] = std::make_shared<node>(node{});
                    nxt.emplace_back(p->c[i]);
                }
            }
            std::swap(c, nxt);
        }
        {
            w += 4;
            uint sum = 0;
            for (auto &p : c) {
                for (uint i = 0; i < 16; ++i) {
                    if (v.size() <= sum + i) break;
                    p->c[i] = std::make_shared<node>(node{v[sum + i]});
                }
                sum += 16U;
            }
        }
    }

    int set(int p, T v, int t = -1) {
        if (t == -1) {
            t = static_cast<int>(root.size()) - 1;
        }
        root.emplace_back(std::make_shared<node>(*root[t]));
        set(root.back(), p, v, w);
        return static_cast<int>(root.size()) - 1;
    }
    void set(nptr &ptr, int p, T v, int w) {
        if (w == 0) {
            ptr->v = v;
            return;
        }
        w -= 4;
        ptr->c[p >> w] = std::make_shared<node>(*(ptr->c[p >> w]));
        set(ptr->c[p >> w], p & ((1 << w) - 1), v, w);
    }

    T get(int p, int t = -1) {
        if (t == -1) {
            t = static_cast<int>(root.size()) - 1;
        }
        return get(root[t], p, w);
    }
    T get(const nptr &ptr, int p, int w) {
        if (w == 0) {
            return ptr->v;
        }
        w -= 4;
        return get(ptr->c[p >> w], p & ((1 << w) - 1), w);
    }
};
