#pragma once
#include <algorithm>
#include <data_structure/segment_tree.hpp>
#include <math/point.hpp>

template <typename T, auto op, auto e, typename S = int>
struct SegmentTree2D {
    int n;
    std::vector<SegmentTree<T, op, e>> seg;
    std::vector<S> X;
    std::vector<std::vector<S>> pos;
    explicit SegmentTree2D(std::vector<Point<S>> p) {
        for (auto [_x, _] : p) {
            X.emplace_back(_x);
        }
        std::sort(X.begin(), X.end());
        X.erase(std::unique(X.begin(), X.end()), X.end());
        n = (1 << (std::__lg(std::max(1, static_cast<int>(X.size()))) + 1)) << 1;
        pos.assign(n * 2, {});
        for (auto [_x, _y] : p) {
            _x = std::distance(X.begin(), std::lower_bound(X.begin(), X.end(), _x));
            _x += n;
            for (; _x; _x >>= 1) {
                pos[_x].emplace_back(_y);
            }
        }
        for (int i = n * 2 - 1; i; --i) {
            std::sort(pos[i].begin(), pos[i].end());
            pos[i].erase(unique(pos[i].begin(), pos[i].end()), pos[i].end());
        }
        seg.emplace_back(SegmentTree<T, op, e>(0));
        for (int i = 1; i < n * 2; ++i) {
            seg.emplace_back(SegmentTree<T, op, e>(pos[i].size()));
        }
    }

    void set(Point<S> p, T v) {
        set(p.x, p.y, v);
    }

    void set(S x, S y, T v) {
        x = distance(X.begin(), lower_bound(X.begin(), X.end(), x));
        x += n;
        {
            int p = distance(pos[x].begin(), lower_bound(pos[x].begin(), pos[x].end(), y));
            seg[x].set(p, v);
        }
        while (x >>= 1) {
            int p = std::distance(pos[x].begin(), std::lower_bound(pos[x].begin(), pos[x].end(), y));
            auto left = lower_bound(pos[x << 1].begin(), pos[x << 1].end(), y);
            auto right = lower_bound(pos[(x << 1) + 1].begin(), pos[(x << 1) + 1].end(), y);
            if (left == pos[x << 1].end() || *left != y) {
                seg[x].set(p, seg[(x << 1) + 1][distance(pos[(x << 1) + 1].begin(), right)]);
            } else if (right == pos[(x << 1) + 1].end() || *right != y) {
                seg[x].set(p, seg[x << 1][distance(pos[x << 1].begin(), left)]);
            } else {
                seg[x].set(p, op(
                                  seg[x << 1][distance(pos[x << 1].begin(), left)],
                                  seg[(x << 1) + 1][distance(pos[(x << 1) + 1].begin(), right)]));
            }
        }
    }

    void add(Point<S> p, T v) {
        add(p.x, p.y, v);
    }

    void add(S x, S y, T v) {
        x = distance(X.begin(), lower_bound(X.begin(), X.end(), x));
        x += n;
        for (; x; x >>= 1) {
            int p = std::distance(pos[x].begin(), std::lower_bound(pos[x].begin(), pos[x].end(), y));
            seg[x].add(p, v);
        }
    }

    T get(S x, S y) {
        x = distance(X.begin(), lower_bound(X.begin(), X.end(), x));
        x += n;
        int p = distance(pos[x].begin(), lower_bound(pos[x].begin(), pos[x].end(), y));
        return seg[x][p];
    }

    T operator()(S l, S r, S t, S b) {
        l = distance(X.begin(), lower_bound(X.begin(), X.end(), l));
        r = distance(X.begin(), lower_bound(X.begin(), X.end(), r));
        T left = e(), right = e();
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                int L = distance(pos[l].begin(), lower_bound(pos[l].begin(), pos[l].end(), t));
                int R = distance(pos[l].begin(), lower_bound(pos[l].begin(), pos[l].end(), b));
                left = op(left, seg[l](L, R));
                ++l;
            }
            if (r & 1) {
                --r;
                int L = distance(pos[r].begin(), lower_bound(pos[r].begin(), pos[r].end(), t));
                int R = distance(pos[r].begin(), lower_bound(pos[r].begin(), pos[r].end(), b));
                right = op(seg[r](L, R), right);
            }
        }
        return op(left, right);
    }
};
