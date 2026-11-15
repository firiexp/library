#define STANDALONE

#include <bits/stdc++.h>
using namespace std;

#include "../geometry/convex_hull.cpp"
#include "../geometry/convex_hull_support.cpp"

__int128 dot(IntPoint p, IntPoint d) {
    return __int128(p.x) * d.x + __int128(p.y) * d.y;
}

void check(const vector<IntPoint> &hull, const ConvexHullSupport &support, IntPoint d) {
    auto result = support.max_dot(d);
    if (hull.empty()) {
        assert(!result);
        return;
    }
    assert(result);
    auto [value, index] = *result;
    assert(0 <= index && index < (int)hull.size());
    assert(value == dot(hull[index], d));
    for (auto point : hull) assert(value >= dot(point, d));
}

void check_rotations(vector<IntPoint> hull, const vector<IntPoint> &directions) {
    for (int rotation = 0; rotation < max(1, (int)hull.size()); ++rotation) {
        ConvexHullSupport support(hull);
        auto copy = support;
        for (auto d : directions) {
            check(hull, support, d);
            check(hull, copy, d);
        }
        for (int i = 0; i < (int)hull.size(); ++i) {
            auto a = hull[i], b = hull[(i + 1) % hull.size()];
            long long dx = b.x - a.x, dy = b.y - a.y;
            long long scale = gcd(abs(dx), abs(dy));
            if (scale) dx /= scale, dy /= scale;
            check(hull, support, {dy, -dx});
            check(hull, support, {-dy, dx});
        }
        if (!hull.empty()) rotate(hull.begin(), hull.begin() + 1, hull.end());
    }
}

int main() {
    vector<IntPoint> directions;
    for (int x = -5; x <= 5; ++x)
        for (int y = -5; y <= 5; ++y) directions.push_back({x, y});
    vector<IntPoint> grid;
    for (int x = -1; x <= 1; ++x)
        for (int y = -1; y <= 1; ++y) grid.push_back({x, y});
    for (int mask = 0; mask < (1 << 9); ++mask) {
        vector<IntPoint> points;
        for (int i = 0; i < 9; ++i) if ((mask >> i) & 1) points.push_back(grid[i]);
        check_rotations(convex_hull(points), directions);
    }
    const long long limit = 1000000000000000000LL;
    for (long long x : {-limit, 0LL, limit})
        for (long long y : {-limit, 0LL, limit}) directions.push_back({x, y});
    check_rotations({{-limit, -limit}, {limit, -limit}, {limit, limit}, {-limit, limit}}, directions);
    check_rotations(convex_hull({{-limit, -limit}, {-limit + 1, -limit},
                                 {limit, limit - 1}, {limit, limit}}), directions);
    check_rotations({{-limit, limit}, {limit, -limit}}, directions);
    check_rotations({{limit, -limit}}, directions);
    mt19937_64 rng(437);
    for (int trial = 0; trial < 1500; ++trial) {
        vector<IntPoint> points(rng() % 60);
        for (auto &p : points) {
            long long range = trial % 2 ? limit : 20;
            p.x = (long long)(rng() % (2 * range + 1)) - range;
            p.y = (long long)(rng() % (2 * range + 1)) - range;
        }
        vector<IntPoint> queries{ {0, 0}, {1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        for (int i = 0; i < 20; ++i)
            queries.push_back({(long long)(rng() % (2 * limit + 1)) - limit,
                               (long long)(rng() % (2 * limit + 1)) - limit});
        check_rotations(convex_hull(points), queries);
    }
    vector<IntPoint> parabola;
    for (long long x = -10000; x <= 10000; ++x) parabola.push_back({x, x * x});
    auto hull = convex_hull(parabola);
    ConvexHullSupport support(hull);
    for (int i = 0; i < 1000; ++i) {
        long long x = (long long)(rng() % 20001) - 10000;
        auto result = support.max_dot({2 * x, -1});
        assert(result && result->first == x * x && hull[result->second] == IntPoint(x, x * x));
    }
    auto owned = ConvexHullSupport(convex_hull(vector<IntPoint>{ {0, 0}, {1, 0}, {0, 1}}));
    assert(owned.max_dot({1, 0})->first == 1);
}
