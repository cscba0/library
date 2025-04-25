#pragma once
#include <data_structure/point.hpp>
#include <vector>

constexpr int DX[8] = {-1, 0, 1, 0, -1, 1, 1, -1};
constexpr int DY[8] = {0, -1, 0, 1, -1, -1, 1, 1};
constexpr bool GRIDMOVE(Point<>& cur, int type, int h, int w, int& time, int top = 0, int left = 0) {
    for (++time;; ++time) {
        if (time) {
            cur.y -= DY[time - 1];
            cur.x -= DX[time - 1];
        }
        if (time == type) return false;
        cur.y += DY[time];
        cur.x += DX[time];
        if (cur.y < top or h <= cur.y or cur.x < left or w <= cur.x) continue;
        return true;
    }
}

#define OVERLOAD_GRID(_1, _2, _3, _4, _5, name, ...) name
#define GRID1(cur, nex) \
    Point nex = cur;    \
    int GTIME = -1;     \
    while (GRIDMOVE(nex, 4, h, w, GTIME))
#define GRID2(cur, nex, type) \
    Point nex = cur;          \
    int GTIME = -1;           \
    while (GRIDMOVE(nex, type, h, w, GTIME))
#define GRID3(cur, nex, type, h) \
    Point nex = cur;             \
    int GTIME = -1;              \
    while (GRIDMOVE(nex, type, h, w, GTIME))
#define GRID4(cur, nex, type, h, w) \
    Point nex = cur;                \
    int GTIME = -1;                 \
    while (GRIDMOVE(nex, type, h, w, GTIME))
#define GRID(...) OVERLOAD_GRID(__VA_ARGS__, GRID4, GRID3, GRID2, GRID1)(__VA_ARGS__)
using GRID = std::vector<std::vector<char>>;
