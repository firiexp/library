#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../geometry/geometry.cpp"

void check(Point a, Point b) {
    long double cross_value = (long double)a.x * b.y - (long double)a.y * b.x;
    long double dot_value = (long double)a.x * b.x + (long double)a.y * b.y;
    long double expected = atan2l(fabsl(cross_value), dot_value);
    double actual = angle(a, b);
    assert(isfinite(actual));
    assert(0 <= actual && actual <= pi);
    assert(fabsl(actual - expected) <= 1e-14L);
}

int main() {
    Point a(1, 5);
    assert(angle(a, a) == 0);
    assert(angle(a, a * -1) == pi);
    assert(angle(Point(1, 0), Point(0, 1)) == pi / 2);
    check(Point(1, 1), Point(1, 1 + 1e-12));
    check(Point(1, 1), Point(-1, -1 + 1e-12));
    array<Point, 3> points{Point(0, 0), Point(1, 5), Point(2, 10)};
    double largest = 0;
    for (int i = 0; i < 3; ++i) {
        largest = max(largest, angle(points[(i + 1) % 3] - points[i],
                                    points[(i + 2) % 3] - points[i]));
    }
    assert(largest == pi);
    vector<Point> vectors;
    for (int x = -20; x <= 20; ++x) for (int y = -20; y <= 20; ++y)
        if (x != 0 || y != 0) vectors.emplace_back(x, y);
    for (Point u : vectors) for (Point v : vectors) check(u, v);
    mt19937 rng(126);
    uniform_int_distribution<int> coord(-1000000000, 1000000000);
    for (int i = 0; i < 1000000; ++i) {
        Point u(coord(rng), coord(rng)), v(coord(rng), coord(rng));
        if ((u.x != 0 || u.y != 0) && (v.x != 0 || v.y != 0)) check(u, v);
    }
    Scanner sc;
    Printer pr;
    int x, y;
    sc.read(x, y);
    pr.println(x + y);
}
