#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <deque>
#include <iostream>
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

int main() {
    self_check();
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
