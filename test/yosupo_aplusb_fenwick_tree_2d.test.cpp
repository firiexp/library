#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../datastructure/range_query_2d/fenwick_tree_2d.cpp"

struct Weight {
    long long value;
    Weight(long long value = 0) : value(value) {}
    Weight &operator+=(Weight other) {
        value += other.value;
        return *this;
    }
    Weight operator-(Weight other) const { return Weight(value - other.value); }
};

void boundary_check() {
    for (int n : {0, 1, 2, 3, 7, 8, 9, 15, 16, 17, 31, 32, 33, 63, 64, 65}) {
        for (int mode = 0; mode < 3; ++mode) {
            FenwickTree2D<Weight> fw;
            vector<tuple<int, int, long long>> points;
            for (int i = 0; i < n; ++i) {
                int x = mode == 1 ? 0 : 2 * i - n;
                int y = mode == 2 ? 0 : 2 * ((i * 17) % n) - n;
                fw.add_point(x, y);
                points.emplace_back(x, y, i % 7 - 3);
            }
            fw.build();
            for (auto [x, y, w] : points) fw.add(x, y, Weight(w));
            auto check_rectangle = [&](int l, int d, int r, int u) {
                long long expected = 0;
                for (auto [x, y, w] : points) {
                    if (l <= x && x < r && d <= y && y < u) expected += w;
                }
                assert(fw.sum(l, d, r, u).value == expected);
            };
            for (int l = -n - 1; l <= n + 1; ++l) {
                for (int r = l; r <= n + 1; ++r) {
                    check_rectangle(l, -n - 1, r, n + 1);
                    check_rectangle(-n - 1, l, n + 1, r);
                    check_rectangle(l, l, r, r);
                }
            }
        }
    }
}

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

void weighted_check() {
    mt19937 rng(328);
    for (int tc = 0; tc < 240; ++tc) {
        int n = tc % 60;
        FenwickTree2D<Weight> bulk, incremental;
        vector<Weight> initial(tc % 4 == 0 ? 0 : tc % 4 == 1 ? n / 3 : n);
        vector<pair<int, int>> points;
        vector<long long> weights(n);
        for (int i = 0; i < n; ++i) {
            int x = tc % 5 == 0 ? 0 : int(rng() % 9) - 4;
            int y = tc % 5 == 1 ? 0 : int(rng() % 9) - 4;
            points.emplace_back(x, y);
            bulk.add_point(x, y);
            incremental.add_point(x, y);
            if (i < int(initial.size())) {
                weights[i] = int(rng() % 21) - 10;
                initial[i] = weights[i];
            }
        }
        bulk.build(initial);
        incremental.build();
        for (int i = 0; i < int(initial.size()); ++i) {
            incremental.add(points[i].first, points[i].second, initial[i]);
        }
        assert(bulk.points == points);
        for (int step = 0; step < 4; ++step) {
            for (int l = -5; l <= 5; ++l) for (int r = l; r <= 5; ++r) {
                for (int d = -5; d <= 5; ++d) for (int u = d; u <= 5; ++u) {
                    long long expected = 0;
                    for (int i = 0; i < n; ++i) {
                        auto [x, y] = points[i];
                        if (l <= x && x < r && d <= y && y < u) expected += weights[i];
                    }
                    assert(bulk.sum(l, d, r, u).value == expected);
                    assert(incremental.sum(l, d, r, u).value == expected);
                }
            }
            if (n) {
                int i = rng() % n;
                int delta = int(rng() % 21) - 10;
                weights[i] += delta;
                bulk.add(points[i].first, points[i].second, Weight(delta));
                incremental.add(points[i].first, points[i].second, Weight(delta));
            }
        }
    }
}

int main() {
    weighted_check();
    boundary_check();
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
}
