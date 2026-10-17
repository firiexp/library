#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../geometry/polygon_integral.cpp"
#include "../geometry/convex_hull.cpp"

void same(PolygonIntegral::RationalPoint a, PolygonIntegral::RationalPoint b) {
    assert(a.x_num == b.x_num && a.y_num == b.y_num && a.den == b.den);
}

void check_result(const PolygonIntegral::Result &actual, const vector<IntPoint> &polygon) {
    __int128 d = 0, x = 0, y = 0;
    int n = polygon.size();
    for (int i = 1; i + 1 < n; ++i) {
        auto a = polygon[0], b = polygon[i], c = polygon[i + 1];
        __int128 bx = (__int128)b.x - a.x, by = (__int128)b.y - a.y;
        __int128 cx = (__int128)c.x - a.x, cy = (__int128)c.y - a.y;
        __int128 area2 = bx * cy - by * cx;
        d += area2;
        x += ((__int128)a.x + b.x + c.x) * area2;
        y += ((__int128)a.y + b.y + c.y) * area2;
    }
    assert(actual.area2() == d);
    auto centroid = actual.centroid();
    assert(centroid.has_value() == (d != 0));
    if (centroid) {
        assert(centroid->den > 0);
        assert(centroid->den == 3 * (d < 0 ? -d : d));
        assert(centroid->x_num == (d < 0 ? -x : x));
        assert(centroid->y_num == (d < 0 ? -y : y));
    }
}

void check(const vector<IntPoint> &points) {
    auto input = points;
    const PolygonIntegral index(input);
    assert(input == points);
    input.clear();
    check_result(index.whole(), points);
    int n = points.size();
    auto reversed = points;
    reverse(reversed.begin(), reversed.end());
    const PolygonIntegral reverse_index(reversed);
    for (int u = 0; u < n; ++u) for (int v = 0; v < n; ++v) {
        vector<IntPoint> cut{points[u]};
        for (int i = u; i != v;) {
            i = (i + 1) % n;
            cut.push_back(points[i]);
        }
        auto result = index.query(u, v);
        check_result(result, cut);
        auto backward = reverse_index.query(n - 1 - v, n - 1 - u);
        assert(backward.area2() == -result.area2());
        assert(backward.centroid().has_value() == result.centroid().has_value());
        if (result.centroid()) {
            same(*result.centroid(), *backward.centroid());
        }
        if (u != v) {
            auto complement = index.query(v, u);
            assert(result.area2() + complement.area2() == index.whole().area2());
        }
    }
}

void transform_check(const vector<IntPoint> &points) {
    const PolygonIntegral original(points);
    vector<IntPoint> transformed;
    for (auto p : points) transformed.emplace_back(-3 * p.x + 7, -3 * p.y - 11);
    const PolygonIntegral moved(transformed);
    int n = points.size();
    for (int u = 0; u < n; ++u) for (int v = 0; v < n; ++v) {
        auto a = original.query(u, v), b = moved.query(u, v);
        assert(b.area2() == 9 * a.area2());
        if (a.centroid()) {
            auto p = *a.centroid(), q = *b.centroid();
            assert(q.x_num * p.den == (-3 * p.x_num + 7 * p.den) * q.den);
            assert(q.y_num * p.den == (-3 * p.y_num - 11 * p.den) * q.den);
        } else assert(!b.centroid());
    }
    check(transformed);
}

void self_check() {
    check({});
    check({{7, 9}});
    check({{7, 9}, {-3, 2}});
    check({{0, 0}, {1, 1}, {2, 2}, {3, 3}});
    check({{0, 0}, {2, 0}, {4, 0}, {4, 2}, {0, 2}});
    vector<IntPoint> triangle{{0, 0}, {1, 0}, {0, 1}};
    check(triangle);
    auto small = PolygonIntegral(triangle).whole();
    assert(small.area2() == 1);
    same(*small.centroid(), {1, 1, 3});
    vector<IntPoint> rectangle{{0, 0}, {4, 0}, {4, 2}, {0, 2}};
    check(rectangle);
    const PolygonIntegral index(rectangle);
    assert(index.whole().area2() == 16);
    same(*index.whole().centroid(), {96, 48, 48});
    same(*index.query(0, 2).centroid(), {64, 16, 24});
    same(*index.query(2, 0).centroid(), {32, 32, 24});
    auto center = *index.whole().centroid();
    assert(center.x_num == 2 * center.den);
    assert(center.x_num % center.den == 0);
    for (long long k : {LLONG_MAX - 4, LLONG_MIN + 4}) {
        check({{k, 0}, {k + 1, 0}, {k + 1, 1}});
        check({{0, k}, {0, k + 1}, {1, k + 1}});
        auto wide = PolygonIntegral({{k, 0}, {k + 1, 0}, {k + 1, 1}}).whole();
        same(*wide.centroid(), {(__int128)3 * k + 2, 1, 3});
    }
    check({{-1000000000, -1000000000}, {1000000000, -1000000000},
           {1000000000, 1000000000}, {-1000000000, 1000000000}});
    mt19937_64 rng(236);
    for (int tc = 0; tc < 500; ++tc) {
        vector<IntPoint> points(1 + rng() % 30);
        for (auto &p : points) p = {int(rng() % 41) - 20, int(rng() % 41) - 20};
        points = convex_hull(points);
        check(points);
        transform_check(points);
        reverse(points.begin(), points.end());
        check(points);
    }
}

int main() {
    self_check();
    Scanner in;
    Printer out;
    int a, b;
    in.read(a, b);
    out.println(a + b);
}
