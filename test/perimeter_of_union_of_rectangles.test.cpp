#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../geometry/perimeter_of_union_of_rectangles.cpp"

using Rect = array<int, 4>;

long long brute(const vector<Rect> &rects) {
    set<pair<int, int>> cells;
    for (auto [l, d, r, u] : rects)
        for (int x = l; x < r; ++x)
            for (int y = d; y < u; ++y) cells.emplace(x, y);
    long long answer = 0;
    for (auto [x, y] : cells)
        for (auto [dx, dy] : vector<pair<int, int>>{{1, 0}, {-1, 0}, {0, 1}, {0, -1}})
            answer += !cells.count({x + dx, y + dy});
    return answer;
}

void check(const vector<Rect> &rects) {
    PerimeterOfUnionOfRectangles<int> solver;
    vector<Rect> prefix;
    assert(solver.solve() == 0);
    for (auto rect : rects) {
        auto [l, d, r, u] = rect;
        solver.add_rectangle(l, d, r, u);
        prefix.push_back(rect);
        assert(solver.solve() == brute(prefix));
        assert(solver.solve() == brute(prefix));
    }
}

int main() {
    check({{0, 0, 2, 2}, {2, 0, 4, 2}, {4, 2, 6, 4}});
    check({{0, 0, 2, 1}, {2, 2, 4, 3}});
    check({{0, 0, 4, 4}, {1, 1, 2, 2}, {0, 0, 4, 4}});
    check({{0, 0, 4, 1}, {0, 3, 4, 4}, {0, 1, 1, 3}, {3, 1, 4, 3}});
    mt19937 rng(307);
    for (int rep = 0; rep < 2000; ++rep) {
        vector<Rect> rects(rng() % 12);
        for (auto &rect : rects) {
            for (int &x : rect) x = int(rng() % 9) - 4;
            if (rep & 1) {
                if (rect[0] > rect[2]) swap(rect[0], rect[2]);
                if (rect[1] > rect[3]) swap(rect[1], rect[3]);
            }
        }
        check(rects);
    }
    PerimeterOfUnionOfRectangles<long long, __int128> wide;
    wide.add_rectangle(LLONG_MIN, LLONG_MIN, LLONG_MAX, LLONG_MAX);
    assert(wide.solve() == 4 * (__int128(LLONG_MAX) - LLONG_MIN));
    PerimeterOfUnionOfRectangles<double, double> fractional;
    fractional.add_rectangle(0.25, 0.5, 1.25, 2.5);
    fractional.add_rectangle(1.25, 0.5, 2.25, 2.5);
    assert(fractional.solve() == 8);
}
