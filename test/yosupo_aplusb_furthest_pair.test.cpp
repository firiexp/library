#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include "../util/fastio.cpp"
#include "../geometry/convex_hull.cpp"
#include "../geometry/furthest_pair.cpp"

__int128 distance_squared(IntPoint a, IntPoint b) {
    __int128 dx = a.first;
    __int128 dy = a.second;
    dx -= b.first;
    dy -= b.second;
    return dx * dx + dy * dy;
}

void check(const vector<IntPoint> &points) {
    const auto original = points;
    auto [i, j] = furthest_pair(points);
    int n = points.size();
    assert(0 <= i && i < n && 0 <= j && j < n && i != j);
    __int128 best = 0;
    for (int u = 0; u < n; ++u)
        for (int v = u + 1; v < n; ++v)
            best = max(best, distance_squared(points[u], points[v]));
    assert(distance_squared(points[i], points[j]) == best);
    assert(points == original);
}

void check_furthest_pair() {
    mt19937_64 rng(20261007);
    for (int mask = 1; mask < (1 << 9); ++mask) {
        vector<IntPoint> points;
        for (int i = 0; i < 9; ++i)
            if (mask >> i & 1) points.emplace_back(i % 3, i / 3);
        if (points.size() > 1) check(points);
        points.push_back(points[0]);
        points.push_back(points[0]);
        shuffle(points.begin(), points.end(), rng);
        check(points);
    }
    check({{40, 880}, {350, 80}, {450, 130}, {750, 300},
           {315, 164}, {940, 770}, {897, 663}, {850, 790}});
    check({{4, -7}, {4, -2}, {4, 0}, {4, 9}});
    check({{-7, 4}, {-2, 4}, {0, 4}, {9, 4}});
    for (int tc = 0; tc < 3000; ++tc) {
        vector<IntPoint> points(2 + rng() % 40);
        for (auto &[x, y] : points) {
            x = int(rng() % 101) - 50;
            y = int(rng() % 101) - 50;
            if (tc % 10 == 0) x = y = 3;
            if (tc % 10 == 1) y = 3 * x + 7;
        }
        check(points);
    }
    const ll limit = 1000000000000000000LL;
    check({{-limit, -limit}, {limit, -limit}, {limit, limit}, {-limit, limit}});
    check({{-limit, -limit}, {-limit + 1, -limit}, {limit, limit - 1}, {limit, limit}});
    check({{-limit, -limit}, {0, 0}, {limit, limit}, {limit, limit}});
    check({{limit, limit}, {limit, limit}});
    const vector<ll> coords{-limit, -limit + 1, -4000000000LL, -1, 0, 1, 4000000000LL, limit - 1, limit};
    for (int tc = 0; tc < 500; ++tc) {
        vector<IntPoint> points(2 + rng() % 30);
        for (auto &[x, y] : points) {
            x = coords[rng() % coords.size()];
            y = coords[rng() % coords.size()];
        }
        check(points);
    }
}

int main() {
    check_furthest_pair();
    Scanner in;
    Printer out;
    int a, b;
    in.read(a, b);
    out.println(a + b);
}
