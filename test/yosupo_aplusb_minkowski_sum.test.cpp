#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include "../util/fastio.cpp"
#include "../geometry/convex_hull.cpp"
#include "../geometry/minkowski_sum.cpp"

vector<IntPoint> brute_hull(vector<IntPoint> points) {
    sort(points.begin(), points.end());
    points.erase(unique(points.begin(), points.end()), points.end());
    if (points.size() <= 2) return points;
    vector<IntPoint> result;
    IntPoint p = points[0];
    do {
        result.push_back(p);
        IntPoint q = p == points[0] ? points[1] : points[0];
        for (IntPoint r : points) {
            __int128 x = (__int128)q.x - p.x, y = (__int128)q.y - p.y;
            __int128 u = (__int128)r.x - p.x, v = (__int128)r.y - p.y;
            __int128 turn = x * v - y * u;
            if (turn < 0 || (turn == 0 && u * u + v * v > x * x + y * y)) q = r;
        }
        p = q;
    } while (p != result[0]);
    return result;
}

void check(vector<IntPoint> a, vector<IntPoint> b) {
    auto original_a = a, original_b = b;
    vector<IntPoint> sums;
    for (auto p : a) for (auto q : b) sums.emplace_back(p.x + q.x, p.y + q.y);
    auto expected = brute_hull(sums);
    assert(minkowski_sum(a, b) == expected);
    assert(a == original_a && b == original_b);
    assert(minkowski_sum(b, a) == expected);
}

vector<IntPoint> large_polygon(int k, int offset) {
    vector<IntPoint> result;
    ll x = 0, y = 0;
    for (int quadrant = 0; quadrant < 4; ++quadrant) {
        for (int i = 0; i < k; ++i) {
            result.emplace_back(x, y);
            ll dx = 1, dy = 4LL * i + offset;
            for (int j = 0; j < quadrant; ++j) {
                ll old_dx = dx;
                dx = -dy;
                dy = old_dx;
            }
            x += dx;
            y += dy;
        }
    }
    assert(x == 0 && y == 0);
    return result;
}

int main() {
    vector<vector<IntPoint>> hulls;
    for (int mask = 0; mask < 512; ++mask) {
        vector<IntPoint> points;
        for (int i = 0; i < 9; ++i) if (mask >> i & 1) points.emplace_back(i % 3, i / 3);
        hulls.push_back(convex_hull(points));
    }
    for (const auto &a : hulls) for (const auto &b : hulls) check(a, b);
    mt19937_64 rng(137);
    const ll limit = 1000000000000000000LL;
    const vector<ll> coords{-limit, -limit + 1, -1, 0, 1, limit - 1, limit};
    for (int tc = 0; tc < 4000; ++tc) {
        vector<IntPoint> a(rng() % 12), b(rng() % 12);
        for (auto *points : {&a, &b}) {
            for (auto &[x, y] : *points) {
                x = tc % 2 ? coords[rng() % coords.size()] : ll(rng() % 101) - 50;
                y = tc % 2 ? coords[rng() % coords.size()] : ll(rng() % 101) - 50;
            }
            *points = convex_hull(*points);
            if (!points->empty()) rotate(points->begin(), points->begin() + rng() % points->size(), points->end());
        }
        check(a, b);
    }
    auto a = large_polygon(12500, 1), b = large_polygon(12500, 3);
    auto sum = minkowski_sum(a, b);
    assert(sum.size() == a.size() + b.size());
    assert(sum[0] == *min_element(sum.begin(), sum.end()));
    for (int i = 0; i < (int)sum.size(); ++i)
        assert(cross(sum[i], sum[(i + 1) % sum.size()], sum[(i + 2) % sum.size()]) > 0);
}
