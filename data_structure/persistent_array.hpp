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
    int w{1};
    int mask = 0b1111;
    PersistentArray(int n) : PersistentArray(std::vector<T>(n, e())) {}
    PersistentArray(int n, T x) : PersistentArray(std::vector<T>(n, x)) {}
    PersistentArray(std::vector<T> v) : root(1, std::make_shared<node>(node{})) {
        if (v.size() == 1U) {
            root[0] = std::make_shared<node>(node{v[0]});
            return;
        }
        std::vector<nptr> c;
        c.emplace_back(root[0]);
        uint siz = 1;
        while (siz * 16 < v.size()) {
            w *= 16;
            mask = (mask << 4) | 0b1111;
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
            w *= 16;
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
        set(root.back(), p, v, w, mask);
        return static_cast<int>(root.size()) - 1;
    }
    void set(nptr &ptr, int p, T v, int w, int mask) {
        if (w == 1) {
            ptr->v = v;
            return;
        }
        ptr->c[p / (w >> 4)] = std::make_shared<node>(*(ptr->c[p / (w >> 4)]));
        set(ptr->c[p / (w >> 4)], p & mask, v, w >> 4, mask >> 4);
    }

    T get(int p, int t = -1) {
        if (t == -1) {
            t = static_cast<int>(root.size()) - 1;
        }
        return get(root[t], p, w, mask);
    }
    T get(const nptr &ptr, int p, int w, int mask) {
        if (w == 1) {
            return ptr->v;
        }
        return get(ptr->c[p / (w >> 4)], p & mask, w >> 4, mask >> 4);
    }
};
