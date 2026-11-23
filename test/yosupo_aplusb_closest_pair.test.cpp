#define STANDALONE

#include <bits/stdc++.h>

using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include <charconv>
#include "../util/fastio.cpp"
#include "../geometry/closest_pair.cpp"

void check(const vector<IntPoint> &points) {
    auto input = points;
    auto [a, b] = closest_pair(input);
    assert(input == points);
    int n = points.size();
    assert(0 <= a && a < n && 0 <= b && b < n && a != b);
    auto distance = [&](int i, int j) {
        auto square = [](long long x, long long y) {
            __int128_t d = __int128_t(x) - y;
            __uint128_t magnitude = d < 0 ? -d : d;
            return magnitude * magnitude;
        };
        auto x = square(points[i].x, points[j].x);
        auto y = square(points[i].y, points[j].y);
        __uint128_t low = __uint128_t(uint64_t(x)) + uint64_t(y);
        return make_pair((x >> 64) + (y >> 64) + (low >> 64), uint64_t(low));
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
    check({{LLONG_MIN, LLONG_MIN / 2}, {LLONG_MAX / 2, LLONG_MAX}, {LLONG_MAX, LLONG_MIN}});
    check({{LLONG_MIN, LLONG_MAX}, {LLONG_MAX, LLONG_MIN}, {0, 0}, {0, 1}});
    for (long long span : {2147483647LL, 2147483648LL, 3037000500LL}) {
        check({{LLONG_MIN, LLONG_MAX}, {LLONG_MIN + span, LLONG_MAX - span},
               {LLONG_MIN + span - 1, LLONG_MAX - span}});
    }
    for (int sign : {-1, 1}) {
        vector<IntPoint> points;
        long long x = -1000000000000000000LL;
        for (int i = 0; i < 24; ++i) {
            x += i == 13 ? 1 : (i + 1) * 100000000LL;
            points.emplace_back(x, sign * (i / 3) * (i / 3));
        }
        rotate(points.begin(), points.begin() + 11, points.end());
        check(points);
    }
    for (int n : {2, 3, 7, 8, 9, 31, 32, 33, 64}) {
        check(vector<IntPoint>(n, {-1, -1}));
        for (int shape = 0; shape < 3; ++shape) {
            vector<IntPoint> points;
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
    for (long long bound : {1000000000000000000LL, LLONG_MAX}) {
        uniform_int_distribution<long long> coordinate(-bound, bound);
        for (int tc = 0; tc < 250; ++tc) {
            vector<IntPoint> points(3 + random() % 60);
            for (auto &[x, y] : points) {
                x = coordinate(random);
                y = coordinate(random);
            }
            check(points);
        }
    }
    for (int tc = 0; tc < 4000; ++tc) {
        int n = 2 + random() % 63;
        vector<IntPoint> points(n);
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
}
