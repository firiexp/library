#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;

#include "../util/fastio.cpp"
#include "../util/modint_base.cpp"
#include "../datastructure/rectangle_add_point_get.cpp"

template<class T>
void check() {
    mt19937 rng(200);
    vector<int> coords = {INT_MIN, -1000000000, -3, -2, -1, 0, 1, 2, 3, 1000000000, INT_MAX};
    for (int tc = 0; tc < 300; ++tc) {
        RectangleAddPointGet<T> solver;
        vector<array<int, 4>> rectangles;
        vector<T> weights, expected;
        auto add = [&](int l, int d, int r, int u, T w) {
            solver.add_rectangle(l, d, r, u, w);
            rectangles.push_back({l, d, r, u});
            weights.push_back(w);
        };
        auto query = [&](int x, int y) {
            solver.add_query(x, y);
            T sum = 0;
            for (int i = 0; i < (int)rectangles.size(); ++i) {
                auto [l, d, r, u] = rectangles[i];
                if (l <= x && x < r && d <= y && y < u) sum += weights[i];
            }
            expected.push_back(sum);
        };
        assert(solver.solve().empty());
        for (int x : coords) query(x, 0);
        assert(solver.solve() == expected);
        if (tc % 3 != 0) {
            add(-2, -3, 2, 3, 7);
            add(-2, -3, 2, 3, -4);
            add(0, -3, 0, 3, 100);
            add(-2, 0, 2, 0, 200);
        }
        for (int x : coords) for (int y : coords) query(x, y);
        assert(solver.solve() == expected);
        for (int step = 0; step < 100; ++step) {
            auto coord = [&]() { return coords[rng() % coords.size()]; };
            if (tc % 3 != 0 && step % 2 == 0) {
                int l = coord(), r = coord(), d = coord(), u = coord();
                if (l > r) swap(l, r);
                if (d > u) swap(d, u);
                add(l, d, r, u, int(rng() % 61) - 30);
            } else {
                query(coord(), coord());
            }
            if (step % 25 == 0) assert(solver.solve() == expected);
        }
        assert(solver.solve() == expected);
        assert(solver.solve() == expected);
    }
}

int main() {
    check<long long>();
    check<modint<998244353>>();
}
