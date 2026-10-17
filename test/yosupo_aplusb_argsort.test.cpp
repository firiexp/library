#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../geometry/argsort.cpp"

int compare(IntPoint a, IntPoint b) {
    return geometry_argsort_detail::compare<__int128>(a.x, a.y, b.x, b.y);
}

void check(const vector<IntPoint> &points, bool small) {
    auto input = points;
    auto order = arg_sort_indices(input);
    assert(input == points);
    auto permutation = order;
    sort(permutation.begin(), permutation.end());
    for (int i = 0; i < int(points.size()); ++i) assert(permutation[i] == i);
    for (int i = 1; i < int(order.size()); ++i) {
        int c = compare(points[order[i - 1]], points[order[i]]);
        assert(c <= 0);
        if (c == 0) assert(order[i - 1] < order[i]);
    }
    argsort(input);
    for (int i = 0; i < int(points.size()); ++i) assert(compare(input[i], points[order[i]]) == 0);
    auto sorted = points;
    sort(sorted.begin(), sorted.end());
    sort(input.begin(), input.end());
    assert(input == sorted);
    if (!small) return;
    vector<int> expected(points.size());
    iota(expected.begin(), expected.end(), 0);
    auto angle = [](IntPoint p) {
        return p.x == 0 && p.y == 0 ? 0.L : atan2l(p.y, p.x);
    };
    stable_sort(expected.begin(), expected.end(), [&](int i, int j) {
        return angle(points[i]) < angle(points[j]);
    });
    assert(order == expected);
    vector<Ar2> narrow;
    for (auto p : points) narrow.push_back({int(p.x), int(p.y)});
    argsort(narrow);
    for (int i = 0; i < int(points.size()); ++i)
        assert(compare({narrow[i][0], narrow[i][1]}, points[order[i]]) == 0);
}

void self_check() {
    check({}, true);
    check({{0, 0}}, true);
    vector<IntPoint> points;
    for (long long x : {LLONG_MIN, -1LL, 0LL, 1LL, LLONG_MAX})
        for (long long y : {LLONG_MIN, -1LL, 0LL, 1LL, LLONG_MAX}) points.emplace_back(x, y);
    check(points, false);
    for (auto a : points) {
        assert(compare(a, a) == 0);
        for (auto b : points) {
            assert(compare(a, b) == -compare(b, a));
            for (auto c : points) {
                if (compare(a, b) < 0 && compare(b, c) < 0) assert(compare(a, c) < 0);
                if (compare(a, b) == 0 && compare(b, c) == 0) assert(compare(a, c) == 0);
            }
        }
    }
    vector<IntPoint> axes{{0, 0}, {3, 0}, {0, 2}, {-2, 0}, {0, -1},
                          {1, 1}, {-1, 1}, {-1, -1}, {1, -1}, {2, 2}, {1, 1}, {0, 0}};
    assert((arg_sort_indices(axes) == vector<int>{7, 4, 8, 0, 1, 11, 5, 9, 10, 2, 6, 3}));
    check(axes, true);
    check({{4000000000LL, 0}, {0, -5000000000LL}, {0, 0}}, false);
    check({{INT_MIN, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MIN, INT_MAX},
           {INT_MAX, INT_MAX}, {0, 0}}, true);
    mt19937_64 rng(231);
    for (int tc = 0; tc < 1000; ++tc) {
        vector<IntPoint> input(rng() % 80);
        for (auto &p : input) p = {int(rng() % 21) - 10, int(rng() % 21) - 10};
        check(input, true);
    }
}

int main() {
    self_check();
    Scanner in;
    Printer out;
    int a, b;
    in.read(a, b);
    out.println(a + b);
}
