#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../datastructure/fenwick_tree_2d.cpp"

void check(vector<pair<int, int>> points, mt19937 &rng) {
    FenwickTree2D<long long> fw;
    map<pair<int, int>, long long> values;
    for (auto [x, y] : points) {
        fw.add_point(x, y);
        values[{x, y}] = 0;
    }
    fw.build();
    assert(fw.points == points);
    assert(fw.sum(INT_MAX, INT_MAX) == 0);
    for (int step = 0; step < 100; ++step) {
        if (!points.empty()) {
            auto [x, y] = points[rng() % points.size()];
            long long w = int(rng() % 201) - 100;
            fw.add(x, y, w);
            values[{x, y}] += w;
        }
        const vector<int> coords{INT_MIN, -1000000000, -7, -1, 0, 1, 7, 1000000000, INT_MAX};
        int l = coords[rng() % coords.size()], r = coords[rng() % coords.size()];
        int d = coords[rng() % coords.size()], u = coords[rng() % coords.size()];
        if (l > r) swap(l, r);
        if (d > u) swap(d, u);
        long long expected = 0, prefix = 0;
        for (auto [point, w] : values) {
            auto [x, y] = point;
            if (l <= x && x < r && d <= y && y < u) expected += w;
            if (x < r && y < u) prefix += w;
        }
        assert(fw.sum(l, d, r, u) == expected);
        assert(fw.sum(r, u) == prefix);
        assert(fw.sum(l, d, l, u) == 0);
        assert(fw.sum(l, d, r, d) == 0);
    }
}

int main() {
    mt19937 rng(112);
    check({}, rng);
    check({{INT_MIN, INT_MIN}, {INT_MAX, INT_MAX}, {0, 0}, {0, 0}}, rng);
    for (int tc = 0; tc < 1000; ++tc) {
        vector<pair<int, int>> points;
        for (int i = 0; i < tc % 65; ++i) {
            int x = int(rng() % 21) - 10;
            int y = tc % 4 == 0 ? 7 : int(rng() % 21) - 10;
            if (tc % 4 == 1) x = int(rng() % 3) - 1;
            points.push_back({x, y});
            if (rng() % 3 == 0) points.push_back({x, y});
        }
        if (tc % 4 == 2) sort(points.begin(), points.end());
        check(points, rng);
    }
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
