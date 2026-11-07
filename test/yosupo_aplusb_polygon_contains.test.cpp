#define STANDALONE

#include <bits/stdc++.h>
using namespace std;

#include "../geometry/polygon_contains.cpp"
#include "../geometry/convex_hull.cpp"

int rational_contains(const vector<IntPoint> &polygon, IntPoint p) {
    int crossings = 0, n = polygon.size();
    for (int i = 0; i < n; ++i) {
        auto a = polygon[i], b = polygon[(i + 1) % n];
        if (a.x == b.x) {
            if (p.x == a.x && min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y)) return 1;
            continue;
        }
        if (a.x > b.x) swap(a, b);
        long long denominator = b.x - a.x;
        long long numerator = a.y * (b.x - p.x) + b.y * (p.x - a.x);
        long long query_numerator = p.y * denominator;
        if (a.x <= p.x && p.x <= b.x && numerator == query_numerator) return 1;
        if (a.x <= p.x && p.x < b.x && numerator > query_numerator) ++crossings;
    }
    return crossings % 2 ? 2 : 0;
}

void check(vector<IntPoint> polygon, bool convex = false) {
    auto original = polygon;
    for (int orientation = 0; orientation < 2; ++orientation) {
        for (int x = -10; x <= 10; ++x) for (int y = -10; y <= 10; ++y) {
            IntPoint p{x, y};
            int expected = rational_contains(original, p);
            assert(contains_polygon(polygon, p) == expected);
            if (convex) assert(contains_convex(original, p) == expected);
        }
        reverse(polygon.begin(), polygon.end());
    }
    assert(polygon == original);
}

int main() {
    check({}, true);
    check({{2, 3}}, true);
    check({{-3, -2}, {5, 6}}, true);
    check({{0, -4}, {0, 4}}, true);
    check({{-4, 0}, {4, 0}}, true);
    check({{0, 0}, {4, 0}, {4, 1}, {1, 1}, {1, 4}, {0, 4}});
    check({{0, 0}, {2, 0}, {4, 0}, {4, 4}, {2, 2}, {0, 4}});
    check({{-8, -4}, {8, -4}, {8, 4}, {6, 4}, {6, -2}, {4, -2},
           {4, 4}, {2, 4}, {2, -2}, {0, -2}, {0, 4}, {-8, 4}});
    for (int mask = 1; mask < (1 << 9); ++mask) {
        vector<IntPoint> points;
        for (int i = 0; i < 9; ++i)
            if (mask >> i & 1) points.emplace_back(i % 3, i / 3);
        check(convex_hull(points), true);
    }
    mt19937_64 rng(435);
    for (int tc = 0; tc < 250; ++tc) {
        vector<IntPoint> polygon;
        for (int x = -8; x <= 8; x += 2) polygon.emplace_back(x, -1 - int(rng() % 8));
        for (int x = 8; x >= -8; x -= 2) polygon.emplace_back(x, 1 + rng() % 8);
        rotate(polygon.begin(), polygon.begin() + rng() % polygon.size(), polygon.end());
        check(polygon);
        for (auto &p : polygon) swap(p.x, p.y);
        check(polygon);
        vector<IntPoint> points(3 + rng() % 25);
        for (auto &p : points) p = {int(rng() % 17) - 8, int(rng() % 17) - 8};
        check(convex_hull(points), true);
    }
    const long long limit = 1000000000000000000LL;
    vector<IntPoint> square{{-limit, -limit}, {limit, -limit}, {limit, limit}, {-limit, limit}};
    assert(contains_polygon(square, {0, 0}) == 2);
    assert(contains_polygon(square, {limit, 0}) == 1);
    assert(contains_polygon(square, {limit, limit}) == 1);
    vector<IntPoint> small{{-8, -8}, {8, -8}, {8, 0}, {0, 0}, {0, 8}, {-8, 8}};
    vector<IntPoint> large = small;
    for (auto &p : large) p = {p.x * (limit / 10), p.y * (limit / 10)};
    for (int x = -10; x <= 10; ++x) for (int y = -10; y <= 10; ++y)
        assert(contains_polygon(large, {x * (limit / 10), y * (limit / 10)}) ==
               rational_contains(small, {x, y}));
    vector<IntPoint> thin{{-limit, -limit}, {limit, limit - 1}, {limit, limit}};
    assert(contains_polygon(thin, {0, 0}) == 1);
    assert(contains_polygon(thin, {0, -1}) == 0);
    assert(contains_polygon(thin, {limit - 1, limit - 2}) == 0);
}
