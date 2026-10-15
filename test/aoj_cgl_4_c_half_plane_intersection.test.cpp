#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_C"
#define ERROR "1e-8"

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

int main() {
    Scanner sc;
    int n;
    sc.read(n);
    Polygon poly(n);
    for (int i = 0; i < n; ++i) {
        ll x, y;
        sc.read(x, y);
        poly[i] = Point(x, y);
    }

    vector<Line> base = polygon_half_planes(poly);
    int q;
    sc.read(q);
    while (q--) {
        ll x1, y1, x2, y2;
        sc.read(x1, y1, x2, y2);
        vector<Line> ls = base;
        ls.emplace_back(Point(x1, y1), Point(x2, y2));
        Polygon ans = half_plane_intersection(ls);
        printf("%.8f\n", fabs(area(ans)));
    }
    return 0;
}
