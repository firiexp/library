#define STANDALONE

#include <bits/stdc++.h>
using namespace std;

#include "../geometry/polygon_lattice_points.cpp"
#include "../geometry/polygon_contains.cpp"
#include "../geometry/convex_hull.cpp"
#include "../geometry/polygon_integral.cpp"

void check_count(vector<IntPoint> polygon, long long interior, long long boundary) {
    for (int orientation = 0; orientation < 2; ++orientation) {
        for (int start = 0; start < int(polygon.size()); ++start) {
            const auto original = polygon;
            auto result = polygon_lattice_points(polygon);
            static_assert(is_same_v<decltype(result.interior), long long>);
            static_assert(is_same_v<decltype(result.boundary), long long>);
            assert(result.interior == interior && result.boundary == boundary);
            assert(polygon == original);
            rotate(polygon.begin(), polygon.begin() + 1, polygon.end());
        }
        reverse(polygon.begin(), polygon.end());
    }
}

void check_small(const vector<IntPoint> &polygon, bool convex = false) {
    long long min_x = polygon[0].x, max_x = min_x, min_y = polygon[0].y, max_y = min_y;
    for (auto p : polygon) {
        min_x = min(min_x, p.x);
        max_x = max(max_x, p.x);
        min_y = min(min_y, p.y);
        max_y = max(max_y, p.y);
    }
    long long interior = 0, boundary = 0;
    for (long long x = min_x; x <= max_x; ++x) for (long long y = min_y; y <= max_y; ++y) {
        int location = contains_polygon(polygon, {x, y});
        interior += location == 2;
        boundary += location == 1;
    }
    check_count(polygon, interior, boundary);
    if (convex) {
        auto result = polygon_lattice_points(polygon);
        auto area2 = PolygonIntegral(polygon).whole().area2();
        if (area2 < 0) area2 = -area2;
        assert(2 * result.interior + result.boundary - 2 == area2);
    }
}

int main() {
    check_count({{0, 0}, {1, 0}, {0, 1}}, 0, 3);
    check_count({{0, 0}, {4, 0}, {4, 2}, {0, 2}}, 3, 12);
    check_count({{0, 0}, {4, 0}, {4, 1}, {1, 1}, {1, 4}, {0, 4}}, 0, 16);
    check_small({{0, 0}, {7, 0}, {3, 5}}, true);
    check_small({{0, 0}, {2, 0}, {4, 0}, {4, 4}, {2, 2}, {0, 4}});
    check_small({{-10, -1}, {-3, -1}, {4, -1}, {10, -1}, {10, 1}, {-10, 1}}, true);
    for (int mask = 1; mask < (1 << 9); ++mask) {
        vector<IntPoint> points;
        for (int i = 0; i < 9; ++i)
            if (mask >> i & 1) points.emplace_back(i % 3, i / 3);
        auto hull = convex_hull(points);
        if (hull.size() >= 3) check_small(hull, true);
    }
    mt19937_64 rng(436);
    for (int tc = 0; tc < 250; ++tc) {
        vector<IntPoint> polygon;
        for (int x = -8; x <= 8; x += 2) polygon.emplace_back(x, -1 - int(rng() % 8));
        for (int x = 8; x >= -8; x -= 2) polygon.emplace_back(x, 1 + rng() % 8);
        check_small(polygon);
        vector<IntPoint> points(3 + rng() % 25);
        for (auto &p : points) p = {int(rng() % 17) - 8, int(rng() % 17) - 8};
        auto hull = convex_hull(points);
        if (hull.size() >= 3) check_small(hull, true);
    }
    const long long limit = 1000000000000000000LL;
    long long width = 2 * limit;
    check_count({{-limit, -limit}, {limit, -limit}, {limit, -limit + 2}, {-limit, -limit + 2}},
                width - 1, 2 * width + 4);
    check_count({{LLONG_MIN, LLONG_MAX - 2}, {LLONG_MIN + 4, LLONG_MAX - 2},
                 {LLONG_MIN + 4, LLONG_MAX}, {LLONG_MIN, LLONG_MAX}}, 3, 12);
    check_count({{LLONG_MAX - 4, LLONG_MIN}, {LLONG_MAX, LLONG_MIN},
                 {LLONG_MAX, LLONG_MIN + 2}, {LLONG_MAX - 4, LLONG_MIN + 2}}, 3, 12);
    check_count({{LLONG_MIN, 0}, {LLONG_MAX - 1, 1}, {LLONG_MAX, 1}, {LLONG_MIN + 1, 0}}, 0, 4);
    check_count({{0, LLONG_MIN}, {1, LLONG_MAX - 1}, {1, LLONG_MAX}, {0, LLONG_MIN + 1}}, 0, 4);
    check_count({{0, 0}, {LLONG_MAX, 1}, {-2, 2}}, LLONG_MAX, 4);
    check_count({{0, 0}, {LLONG_MAX - 2, 0}, {0, 1}}, 0, LLONG_MAX);
}
