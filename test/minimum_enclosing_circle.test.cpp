#define STANDALONE
#include <bits/stdc++.h>
using namespace std;

#include "../util/biginteger.cpp"
#include "../geometry/minimum_enclosing_circle.cpp"
using Big = BigInteger;

struct ExactCircle {
    Big x, y, denominator, radius2;
};

Big distance2(const ExactCircle &circle, const IntPoint &p) {
    Big x = Big(p.x) * circle.denominator - circle.x;
    Big y = Big(p.y) * circle.denominator - circle.y;
    return x * x + y * y;
}

ExactCircle oracle(const vector<IntPoint> &points) {
    optional<ExactCircle> best;
    auto consider = [&](ExactCircle circle) {
        if (circle.denominator < 0) {
            circle.x = -circle.x;
            circle.y = -circle.y;
            circle.denominator = -circle.denominator;
        }
        for (auto p : points) if (distance2(circle, p) > circle.radius2) return;
        if (!best || circle.radius2 * best->denominator * best->denominator
            < best->radius2 * circle.denominator * circle.denominator) best = circle;
    };
    int n = points.size();
    for (int i = 0; i < n; ++i) {
        auto a = points[i];
        consider({a.x, a.y, 1, 0});
        for (int j = 0; j < i; ++j) {
            auto b = points[j];
            Big ux = Big(b.x) - a.x, uy = Big(b.y) - a.y;
            Big u2 = ux * ux + uy * uy;
            consider({Big(a.x) + b.x, Big(a.y) + b.y, 2, u2});
            for (int k = 0; k < j; ++k) {
                auto c = points[k];
                Big vx = Big(c.x) - a.x, vy = Big(c.y) - a.y;
                Big denominator = 2 * (ux * vy - uy * vx);
                if (denominator == 0) continue;
                Big v2 = vx * vx + vy * vy;
                Big dx = u2 * vy - v2 * uy, dy = v2 * ux - u2 * vx;
                consider({Big(a.x) * denominator + dx, Big(a.y) * denominator + dy,
                    denominator, dx * dx + dy * dy});
            }
        }
    }
    assert(best);
    return *best;
}

void check(const vector<IntPoint> &points, uint64_t seed) {
    if (points.empty()) {
        assert(!minimum_enclosing_circle(points, seed));
        return;
    }
    auto expected = oracle(points);
    vector<int> boundary;
    for (int i = 0; i < (int)points.size(); ++i) {
        if (distance2(expected, points[i]) == expected.radius2) boundary.push_back(i);
    }
    long double denominator = stold(expected.denominator.to_string());
    long double x = stold(expected.x.to_string()) / denominator;
    long double y = stold(expected.y.to_string()) / denominator;
    long double radius = sqrtl(stold(expected.radius2.to_string())) / denominator;
    for (uint64_t s : {uint64_t(77), seed, seed + 1}) {
        auto original = points;
        auto actual = minimum_enclosing_circle(original, s);
        assert(original == points);
        assert(actual && actual->boundary_indices == boundary);
        assert(fabsl(actual->center.x - x) <= 1e-8L * (1 + fabsl(x)));
        assert(fabsl(actual->center.y - y) <= 1e-8L * (1 + fabsl(y)));
        assert(fabsl(actual->radius - radius) <= 1e-8L * (1 + radius));
    }
}

int main() {
    mt19937_64 rng(77);
    vector<vector<IntPoint>> cases{
        {}, {{7, -9}}, {{7, -9}, {7, -9}, {7, -9}}, {{0, 0}, {4, 0}},
        {{-5, 2}, {0, 2}, {8, 2}, {-5, 2}}, {{0, 0}, {2, 0}, {1, 1}},
        {{0, 0}, {4, 0}, {2, 3}}, {{0, 0}, {4, 0}, {1, 1}},
        {{5, 0}, {3, 4}, {-3, 4}, {-5, 0}, {-3, -4}, {3, -4}, {0, 0}, {3, 4}},
        {{-1000000000, -1000000000}, {1000000000, 1000000000},
         {-1000000000, 1000000000}, {1000000000, -1000000000}, {0, 0}},
        {{-1000000000, 0}, {1000000000, 0}, {0, 1000000000}, {0, 999999999}},
        {{-1000000000, 0}, {1000000000, 0}, {1, 1000000000}, {0, 999999999}},
        {{-1000000000, -1000000000}, {999999999, 999999998}, {1000000000, 999999999}}
    };
    for (auto &points : cases) check(points, rng());
    for (int mask = 0; mask < 512; ++mask) {
        vector<IntPoint> points;
        for (int j = 0; j < 9; ++j) if (mask >> j & 1) points.emplace_back(j / 3, j % 3);
        check(points, rng());
    }
    for (int tc = 0; tc < 1800; ++tc) {
        vector<IntPoint> points(rng() % 9 + 1);
        for (auto &p : points) {
            if (tc % 3 == 0) {
                p = {(long long)(rng() % 2000000001ULL) - 1000000000LL,
                     (long long)(rng() % 2000000001ULL) - 1000000000LL};
            } else if (tc % 3 == 1) {
                p = {1000000000LL - (long long)(rng() % 20),
                     -1000000000LL + (long long)(rng() % 20)};
            } else {
                p = {(long long)(rng() % 11) - 5, (long long)(rng() % 11) - 5};
            }
        }
        if (tc % 7 == 0) sort(points.begin(), points.end());
        if (tc % 11 == 0) for (auto &p : points) p.y = p.x;
        check(points, rng());
    }
    for (int tc = 0; tc < 30000; ++tc) {
        array<IntPoint, 4> points;
        for (auto &p : points) {
            auto coordinate = [&]() -> long long {
                if (tc % 2) return (long long)(rng() % 2000000001ULL) - 1000000000LL;
                return rng() % 2 ? 1000000000LL : -1000000000LL;
            };
            p = {coordinate(), coordinate()};
        }
        auto disk = minimum_enclosing_circle_detail::through_three(points[0], points[1], points[2]);
        if (disk.size != 3) continue;
        auto a = disk.a, b = disk.b, c = disk.c, p = points[3];
        Big ax = Big(a.x) - p.x, ay = Big(a.y) - p.y;
        Big bx = Big(b.x) - p.x, by = Big(b.y) - p.y;
        Big cx = Big(c.x) - p.x, cy = Big(c.y) - p.y;
        Big determinant = (ax * ax + ay * ay) * (bx * cy - by * cx)
            - (bx * bx + by * by) * (ax * cy - ay * cx)
            + (cx * cx + cy * cy) * (ax * by - ay * bx);
        int expected = (determinant < 0) - (determinant > 0);
        assert(disk.side(p) == expected);
    }
}
