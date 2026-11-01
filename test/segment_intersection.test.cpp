#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../geometry/segment_intersection.cpp"
#include "../geometry/convex_hull.cpp"

bool brute(IntPoint a, IntPoint b, IntPoint c, IntPoint d) {
    long long ux = b.x - a.x, uy = b.y - a.y;
    long long vx = d.x - c.x, vy = d.y - c.y;
    long long wx = c.x - a.x, wy = c.y - a.y;
    long long det = ux * vy - uy * vx;
    if (det != 0) {
        long long t = wx * vy - wy * vx, s = wx * uy - wy * ux;
        if (det < 0) det = -det, t = -t, s = -s;
        return 0 <= t && t <= det && 0 <= s && s <= det;
    }
    auto contains = [](IntPoint p, IntPoint q, IntPoint r) {
        long long dx = q.x - p.x, dy = q.y - p.y;
        long long rx = r.x - p.x, ry = r.y - p.y;
        if (dx == 0 && dy == 0) return p == r;
        long long denominator = dx != 0 ? dx : dy;
        long long numerator = dx != 0 ? rx : ry;
        if (denominator < 0) denominator = -denominator, numerator = -numerator;
        return 0 <= numerator && numerator <= denominator &&
               rx * denominator == dx * numerator && ry * denominator == dy * numerator;
    };
    return contains(a, b, c) || contains(a, b, d) || contains(c, d, a) || contains(c, d, b);
}

int main() {
    vector<IntPoint> points;
    for (int x = -2; x <= 2; ++x)
        for (int y = -2; y <= 2; ++y) points.push_back({x, y});
    for (auto a : points) for (auto b : points) for (auto c : points) for (auto d : points)
        assert(segments_intersect(a, b, c, d) == brute(a, b, c, d));
    auto check = [](IntPoint a, IntPoint b, IntPoint c, IntPoint d, bool expected) {
        for (int i = 0; i < 8; ++i) {
            assert(segments_intersect(a, b, c, d) == expected);
            swap(a, b);
            if (i % 2) swap(c, d);
            if (i % 4 == 3) { swap(a, c); swap(b, d); }
        }
    };
    const long long m = 1000000000000000000LL;
    check({-m, -m}, {m, m}, {-m, m}, {m, -m}, true);
    check({-m, -m}, {m, -m}, {-m, m}, {m, m}, false);
    check({-m, -m}, {m, m}, {m, m}, {m, -m}, true);
    check({-m, 0}, {0, 0}, {1, 0}, {m, 0}, false);
    check({-m, 0}, {1, 0}, {0, 0}, {m, 0}, true);
    check({0, 0}, {0, 0}, {-m, -m}, {m, m}, true);
    check({0, 1}, {0, 1}, {-m, -m}, {m, m}, false);
    check({m, m}, {m, m}, {m, m}, {m, m}, true);
    check({m - 1, m}, {m - 1, m}, {m, m}, {m, m}, false);
}
