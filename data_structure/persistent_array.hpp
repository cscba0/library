#pragma once
#include <array>
#include <memory>
#include <vector>

template <typename T, auto e = []() { return T(); }>
struct PersistentArray {
    struct node;
    using nptr = std::unique_ptr<node>;
    struct node {
        T v{e()};
        std::array<nptr, 20> c;
        node() {}
        node(T _v) : v(_v) {}
    };
    std::vector<nptr> root;
    int w{1};
    PersistentArray(int n) : PersistentArray(std::vector<T>(n, e())) {}
    PersistentArray(std::vector<T> v) {
        root = std::vector<nptr>(1);
        root[0] = std::make_unique<node>(node{});
        if (v.size() == 1U) {
            root[0] = std::make_unique<node>(node{v[0]});
            return;
        }
        std::vector<nptr> c;
        c.emplace_back(root[0]);
        uint siz = 1;
        while (siz * 20 < v.size()) {
            w *= 20;
            std::vector<nptr> nxt;
            for (auto &p : c) {
                for (int i = 0; i < 20; ++i) {
                    p->c[i] = std::make_unique<node>(node{});
                    nxt.emplace_back(p->c[i]);
                }
            }
            std::swap(c, nxt);
        }
        {
            w *= 20;
            uint sum = 0;
            for (auto &p : c) {
                for (uint i = 0; i < 20; ++i) {
                    if (v.size() <= sum + i) break;
                    p->c[i] = std::make_unique<node>(node{v[sum + i]});
                }
                sum += 20U;
            }
        }
    }

    int set(int p, T v, int t = -1) {
        if (t == -1) {
            t = static_cast<int>(root.size()) - 1;
        }
        root.emplace_back(nullptr);
        root.back() = static_cast<nptr>(malloc(sizeof(root[t])));
        mempcpy(root.back(), root[t], sizeof(root[t]));
        set(root.back(), p, v, w);
        return static_cast<int>(root.size()) - 1;
    }
    void set(nptr &ptr, int p, T v, int w) {
        if (w == 1) {
            ptr->v = v;
            return;
        }
        nptr nxt = static_cast<nptr>(malloc(sizeof(ptr->c[p / 20])));
        memcpy(nxt, ptr->c[p / 20], sizeof(ptr->c[p / 20]));
        ptr->c[p / 20] = nxt;
        set(ptr->c[p / 20], p % 20, v, w / 20);
    }

    T get(int p, int t = -1) {
        if (t == -1) {
            t = static_cast<int>(root.size()) - 1;
        }
        return get(root[t], p, w);
    }
    T get(const nptr &ptr, int p, int w) {
        if (w == 1) {
            return ptr->v;
        }
        return get(ptr->c[p / 20], p % 20, w / 20);
    }
};
