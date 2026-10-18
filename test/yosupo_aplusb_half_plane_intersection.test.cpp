#define STANDALONE

#include <algorithm>
#include <cassert>
#include <cmath>
#include <deque>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>
using namespace std;

using ll = long long;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include <charconv>
#include "../util/fastio.cpp"
#include "../geometry/half_plane_intersection.cpp"

vector<Line> polygon_half_planes(const Polygon &poly) {
    vector<Line> ls;
    int n = poly.size();
    ls.reserve(n);
    for (int i = 0; i < n; ++i) {
        ls.emplace_back(poly[i], poly[(i + 1) % n]);
    }
    return ls;
}

void self_check() {
    {
        Polygon poly = {
            Point(1, 1),
            Point(4, 1),
            Point(4, 3),
            Point(1, 3),
        };
        auto ls = polygon_half_planes(poly);
        ls.emplace_back(Point(2, 0), Point(2, 4));
        Polygon got = half_plane_intersection(ls);
        assert(fabs(fabs(area(got)) - 2.0) < 1e-9);
    }
    {
        Polygon poly = {
            Point(1, 1),
            Point(4, 1),
            Point(4, 3),
            Point(1, 3),
        };
        auto ls = polygon_half_planes(poly);
        ls.emplace_back(Point(2, 4), Point(2, 0));
        Polygon got = half_plane_intersection(ls);
        assert(fabs(fabs(area(got)) - 4.0) < 1e-9);
    }
    {
        Polygon poly = {
            Point(0, 0),
            Point(4, 0),
            Point(4, 2),
            Point(2, 4),
            Point(0, 4),
        };
        auto ls = polygon_half_planes(poly);
        ls.emplace_back(Point(5, 5), Point(5, 3));
        Polygon got = half_plane_intersection(ls);
        assert(got.empty());
    }
}

Polygon clipped(Polygon poly, const Line &line) {
    Polygon result;
    auto side = [&](Point p) {
        return (long double)(line.b.x - line.a.x) * (p.y - line.a.y) -
               (long double)(line.b.y - line.a.y) * (p.x - line.a.x);
    };
    for (int i = 0; i < (int)poly.size(); ++i) {
        Point a = poly[i], b = poly[(i + 1) % poly.size()];
        long double da = side(a), db = side(b);
        if (da >= 0) result.push_back(a);
        if ((da < 0 && db > 0) || (da > 0 && db < 0)) {
            long double t = da / (da - db);
            result.emplace_back(a.x + t * (b.x - a.x), a.y + t * (b.y - a.y));
        }
    }
    return result;
}

void regression_check() {
    vector<Line> lines{
        Line(Point(0, 0), Point(1e8, 0)),
        Line(Point(0, 1), Point(1e8, 1.0075)),
        Line(Point(0, 2), Point(1e8, 2.015)),
        Line(Point(0, 3), Point(0, 0)),
        Line(Point(1, 0), Point(1, 3)),
        Line(Point(1, 3), Point(0, 3)),
    };
    using internal_half_plane_intersection::HalfPlane;
    vector<HalfPlane> hs;
    for (const auto &l : lines) hs.emplace_back(l);
    for (const auto &a : hs) for (const auto &b : hs) for (const auto &c : hs) {
        assert(!(a < a));
        assert(!(a < b && b < a));
        if (a < b && b < c) assert(a < c);
        if (!(a < b) && !(b < a) && !(b < c) && !(c < b))
            assert(!(a < c) && !(c < a));
    }
    vector<int> order(lines.size());
    iota(order.begin(), order.end(), 0);
    do {
        vector<Line> permuted;
        for (int i : order) permuted.push_back(lines[i]);
        Polygon got = half_plane_intersection(permuted);
        assert(got.size() == 4);
        assert(fabs(area(got) - (1 - 0.5 * (2.015 - 2) / 1e8)) < 1e-6);
        Polygon expected{Point(0, 2), Point(1, 2 + (2.015 - 2) / 1e8), Point(1, 3), Point(0, 3)};
        for (Point p : expected) {
            assert(any_of(got.begin(), got.end(), [&](Point q) { return abs(p - q) < 1e-6; }));
        }
    } while (next_permutation(order.begin(), order.end()));
}

void parallel_check() {
    Polygon square{Point(0, 0), Point(4, 0), Point(4, 4), Point(0, 4)};
    mt19937 rng(52);
    for (int lower = -1; lower <= 5; ++lower) {
        auto lines = polygon_half_planes(square);
        lines.emplace_back(Point(0, lower), Point(8, lower));
        lines.emplace_back(Point(1, lower), Point(5, lower));
        for (int tc = 0; tc < 30; ++tc) {
            shuffle(lines.begin(), lines.end(), rng);
            auto got = half_plane_intersection(lines);
            if (lower >= 4) assert(got.empty());
            else assert(fabs(area(got) - 4 * (4 - max(0, lower))) < 1e-7);
        }
    }
    auto point = polygon_half_planes(square);
    point.emplace_back(Point(0, 4), Point(4, 4));
    point.emplace_back(Point(4, 4), Point(4, 0));
    assert(half_plane_intersection(point).empty());
    for (int tc = 0; tc < 1000; ++tc) {
        auto lines = polygon_half_planes(square);
        Polygon expected = square;
        for (int i = 0; i < 8; ++i) {
            Point a(int(rng() % 11) - 3, int(rng() % 11) - 3);
            Point b(int(rng() % 11) - 3, int(rng() % 11) - 3);
            if (a.x == b.x && a.y == b.y) continue;
            lines.emplace_back(a, b);
            expected = clipped(expected, lines.back());
        }
        shuffle(lines.begin(), lines.end(), rng);
        Polygon got = half_plane_intersection(lines);
        assert(fabs(area(got) - area(expected)) < 1e-7);
    }
}

int main() {
    self_check();
    regression_check();
    parallel_check();
}
