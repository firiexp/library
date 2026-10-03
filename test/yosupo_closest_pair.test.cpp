#define PROBLEM "https://judge.yosupo.jp/problem/closest_pair"

#include <bits/stdc++.h>

using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include <charconv>
#include "../util/fastio.cpp"
#include "../geometry/closest_pair.cpp"

void check(const vector<pair<long long, long long>> &points) {
    auto input = points;
    auto [a, b] = closest_pair(input);
    assert(input == points);
    int n = points.size();
    assert(0 <= a && a < n && 0 <= b && b < n && a != b);
    auto distance = [&](int i, int j) {
        __int128_t dx = (__int128_t)points[i].first - points[j].first;
        __int128_t dy = (__int128_t)points[i].second - points[j].second;
        return dx * dx + dy * dy;
    };
    auto best = distance(0, 1);
    for (int i = 0; i < n; ++i) for (int j = 0; j < i; ++j) best = min(best, distance(i, j));
    assert(distance(a, b) == best);
}

void self_check() {
    check({{0, 0}, {0, 0}});
    check({{0, 0}, {1, 0}, {0, 1}, {1, 1}});
    check({{-4000000000000000000LL, -4000000000000000000LL},
           {4000000000000000000LL, 4000000000000000000LL}});
    for (int n : {2, 3, 7, 8, 9, 31, 32, 33, 64}) {
        check(vector<pair<long long, long long>>(n, {-1, -1}));
        for (int shape = 0; shape < 3; ++shape) {
            vector<pair<long long, long long>> points;
            for (int i = 0; i < n; ++i) {
                long long t = i - n / 2;
                points.emplace_back(shape == 0 ? 0 : t, shape == 1 ? 0 : 2 * t);
            }
            check(points);
            reverse(points.begin(), points.end());
            check(points);
        }
    }
    mt19937_64 random(53);
    for (int tc = 0; tc < 4000; ++tc) {
        int n = 2 + random() % 63;
        vector<pair<long long, long long>> points(n);
        long long bound = tc % 2 ? 1000000000 : 5;
        for (auto &[x, y] : points) {
            x = (long long)(random() % (2 * bound + 1)) - bound;
            y = (long long)(random() % (2 * bound + 1)) - bound;
        }
        if (tc % 3 == 0) points.back() = points.front();
        check(points);
    }
}

int main() {
    self_check();
    Scanner sc;
    Printer pr;

    int t;
    sc.read(t);
    while (t--) {
        int n;
        sc.read(n);
        vector<pair<long long, long long>> ps(n);
        for (int i = 0; i < n; ++i) {
            sc.read(ps[i].first, ps[i].second);
        }
        auto [a, b] = closest_pair(ps);
        pr.println(a, b);
    }
    return 0;
}
