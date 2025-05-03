#pragma once
#include <chrono>
#include <cstdint>
#include <vector>

template <typename K = uint64_t, typename V = uint64_t, auto f = [](const K& c) { return c; }, auto e = []() { return V{}; }>
struct HashMap {
    uint32_t n, s, shift;
    uint64_t r;
    std::vector<K> k;
    std::vector<V> v;
    std::vector<bool> u;
    HashMap(uint32_t _n = 8) : n(_n), s(0), shift(64 - std::__lg(n)), k(n), v(n), u(n) {
        r = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        r ^= r >> 16;
        r ^= r << 32;
    }
    void reallocate() {
        n <<= 1;
        std::vector<K> nk(n);
        std::vector<V> nv(n);
        std::vector<bool> nu(n);
        --shift;
        for (int i = 0, size = u.size(); i < size; ++i) {
            if (u[i]) {
                uint32_t h = (f(k[i]) * r) >> shift;
                while (nu[h]) {
                    h = (h + 1) & (n - 1);
                }
                nk[h] = k[i];
                nv[h] = v[i];
                nu[h] = 1;
            }
        }
        std::swap(nk, k);
        std::swap(nv, v);
        std::swap(nu, u);
    }
    V& operator[](const K& c) {
        uint32_t h = f(c) * r >> shift;
        while (true) {
            if (!u[h]) {
                if (n <= s + (s >> 2)) {
                    reallocate();
                    return this->operator[](c);
                }
                k[h] = c;
                u[h] = 1;
                ++s;
                return v[h] = e();
            }
            if (k[h] == c) return v[h];
            h = (h + 1) & (n - 1);
        }
    }

    bool contains(const K& c) {
        uint32_t h = f(c) * r >> shift;
        while (true) {
            if (!u[h]) return false;
            if (k[h] == c) return true;
            h = (h + 1) & (n - 1);
        }
    }

    struct Iterator {
        HashMap* map;
        uint32_t idx;

        Iterator(HashMap* m, uint32_t i) : map(m), idx(i) {}

        std::pair<const K&, V&> operator*() {
            return {map->k[idx], map->v[idx]};
        }

        std::pair<const K&, V&> operator*() const {
            return {map->k[idx], map->v[idx]};
        }

        Iterator& operator++() {
            do {
                ++idx;
            } while (idx < map->n && !map->u[idx]);
            return *this;
        }

        bool operator==(const Iterator& other) const {
            return map == other.map && idx == other.idx;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }
    };

    Iterator begin() {
        uint32_t i = 0;
        while (i < n && !u[i]) {
            ++i;
        }
        return Iterator(this, i);
    }

    Iterator end() {
        return Iterator(this, n);
    }
};
