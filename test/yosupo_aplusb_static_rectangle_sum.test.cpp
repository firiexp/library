#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../datastructure/static_rectangle_sum.cpp"

void check(const StaticRectangleSum<long long>& solver) {
    auto points = solver.points;
    auto events = solver.events;
    auto ys = solver.ys;
    vector<long long> expected(events.size() / 2);
    for (auto e : events) {
        for (auto p : points) {
            if (p.x < e.x && e.d <= p.y && p.y < e.u) {
                expected[e.id] += p.w * e.sign;
            }
        }
    }
    for (int repeat = 0; repeat < 3; ++repeat) {
        assert(solver.solve() == expected);
        assert(solver.ys == ys);
        assert(solver.points.size() == points.size());
        assert(solver.events.size() == events.size());
        for (int i = 0; i < (int)points.size(); ++i) {
            auto a = solver.points[i], b = points[i];
            assert(tie(a.x, a.y, a.w) == tie(b.x, b.y, b.w));
        }
        for (int i = 0; i < (int)events.size(); ++i) {
            auto a = solver.events[i], b = events[i];
            assert(tie(a.x, a.d, a.u, a.id, a.sign) == tie(b.x, b.d, b.u, b.id, b.sign));
        }
    }
}

int main() {
    StaticRectangleSum<long long> regression;
    regression.add_point(10, 100, 7);
    regression.add_query(0, 50, 20, 150);
    assert(regression.solve() == vector<long long>{7});
    assert(regression.solve() == vector<long long>{7});
    check(regression);

    mt19937 rng(96);
    const vector<int> coords = {INT_MIN, -100, -1, 0, 1, 50, 100, 150, INT_MAX};
    for (int tc = 0; tc < 300; ++tc) {
        StaticRectangleSum<long long> solver;
        check(solver);
        auto coord = [&]() { return coords[rng() % coords.size()]; };
        for (int step = 0; step < 50; ++step) {
            if (rng() % 2) {
                int x = coord(), y = coord();
                long long w = int(rng() % 101) - 50;
                solver.add_point(x, y, w);
                if (rng() % 3 == 0) solver.add_point(x, y, w);
            } else {
                int l = coord(), r = coord(), d = coord(), u = coord();
                if (l > r) swap(l, r);
                if (d > u) swap(d, u);
                solver.add_query(l, d, r, u);
            }
            if (step % 10 == 0) check(solver);
        }
        check(solver);
    }
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
