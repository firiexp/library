#define STANDALONE

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../geometry/geometry.cpp"

void check(Polygon points, int l = 0, int r = -1) {
    auto original = points;
    int end = r == -1 ? int(points.size()) : r;
    if (r == -1) sort(original.begin(), original.end());
    long double expected = numeric_limits<long double>::infinity();
    for (int i = l; i < end; ++i) for (int j = l; j < i; ++j) {
        long double dx = (long double)original[i].x - original[j].x;
        long double dy = (long double)original[i].y - original[j].y;
        expected = min(expected, hypotl(dx, dy));
    }
    double actual = closest_pair(points, l, r);
    assert(fabsl(actual - expected) <= max(1e-14L, expected * 1e-12L));
    assert(is_sorted(points.begin() + l, points.begin() + end, sorty));
    for (int i = 0; i < int(points.size()); ++i)
        if (i < l || i >= end) assert(points[i].x == original[i].x && points[i].y == original[i].y);
    sort(points.begin() + l, points.begin() + end);
    sort(original.begin() + l, original.begin() + end);
    for (int i = 0; i < int(points.size()); ++i)
        assert(points[i].x == original[i].x && points[i].y == original[i].y);
}

void self_check() {
    check({Point(0, 0), Point(3, 4)});
    check({Point(1e9, -1e9), Point(-1e9, 1e9)});
    check({Point(0, 0), Point(1e-12, 0), Point(0, 2e-12)});
    check({Point(0, 0), Point(1, 0), Point(0, 1), Point(1, 1)});
    check({Point(0, 0), Point(10, 0), Point(20, 0), Point(0, 0)}, 1, 3);
    for (int n : {2, 3, 7, 8, 9, 31, 32, 33, 64}) {
        for (int shape = 0; shape < 5; ++shape) {
            Polygon points;
            for (int i = 0; i < n; ++i) {
                double t = i - n / 2;
                if (shape == 0) points.emplace_back(t, 0);
                if (shape == 1) points.emplace_back(0, t);
                if (shape == 2) points.emplace_back(t, 2 * t);
                if (shape == 3) points.emplace_back(1, 1);
                if (shape == 4) points.emplace_back(i % 8, i / 8);
            }
            check(points);
            reverse(points.begin(), points.end());
            check(points);
        }
    }
    mt19937_64 rng(226);
    for (int tc = 0; tc < 3000; ++tc) {
        int n = 2 + rng() % 79;
        Polygon points;
        double scale = tc % 3 == 0 ? 0.125 : tc % 3 == 1 ? 1e7 : 1e-6;
        for (int i = 0; i < n; ++i)
            points.emplace_back((int(rng() % 81) - 40) * scale, (int(rng() % 81) - 40) * scale);
        check(points);
        sort(points.begin(), points.end());
        int l = rng() % (n - 1), r = l + 2 + rng() % (n - l - 1);
        check(points, l, r);
        check(points, l);
    }
}

int main() {
    self_check();
}
