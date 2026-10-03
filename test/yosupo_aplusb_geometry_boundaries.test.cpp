#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../geometry/geometry.cpp"
#include "../geometry/area_of_union_of_rectangles.cpp"
#include "../graph/manhattanmst.cpp"

void hull_check() {
    auto check = [](Polygon input, const Polygon &expected) {
        auto actual = convex_hull(input);
        assert(actual.size() == expected.size());
        for (int i = 0; i < int(actual.size()); ++i)
            assert(actual[i].x == expected[i].x && actual[i].y == expected[i].y);
    };
    check({}, {});
    check({Point(1, 2)}, {Point(1, 2)});
    check({Point(2, 3), Point(-1, 0)}, {Point(-1, 0), Point(2, 3)});
    Polygon triangle{Point(0, 0), Point(2, 0), Point(0, 2)};
    check({triangle[2], triangle[0], triangle[1]}, triangle);
    Polygon boundary{Point(0, 0), Point(1, 0), Point(2, 0), Point(2, 1),
                     Point(2, 2), Point(1, 2), Point(0, 2), Point(0, 1)};
    Polygon input = boundary;
    input.push_back(Point(1, 1));
    mt19937 rng(47);
    for (int i = 0; i < 20; ++i) {
        shuffle(input.begin(), input.end(), rng);
        check(input, boundary);
    }
}

void contains_convex_check() {
    Polygon empty;
    assert(contains_convex(empty, Point(0, 0)) == 0);
    auto check = [](Polygon polygon) {
        for (int direction = 0; direction < 2; ++direction) {
            for (int start = 0; start < int(polygon.size()); ++start) {
                for (int x = -6; x <= 10; ++x) for (int y = -6; y <= 10; ++y) {
                    Point p(x * 0.5, y * 0.5);
                    assert(contains_convex(polygon, p) == contains(polygon, p));
                }
                rotate(polygon.begin(), polygon.begin() + 1, polygon.end());
            }
            reverse(polygon.begin(), polygon.end());
        }
    };
    check({Point(0, 0)});
    check({Point(0, 0), Point(1, 0)});
    check({Point(0, 0), Point(1, 0), Point(2, 0), Point(3, 0)});
    check({Point(0, 0), Point(1, 0), Point(1, 1), Point(0, 1)});
    check({Point(0, 0), Point(4, 0), Point(0, 4)});
    check({Point(0, 0), Point(1, 0), Point(2, 0), Point(2, 1),
           Point(2, 2), Point(1, 2), Point(0, 2), Point(0, 1)});
    mt19937 rng(16);
    for (int tc = 0; tc < 100; ++tc) {
        set<pair<int, int>> points;
        for (int i = 0; i < 10; ++i) points.emplace(int(rng() % 9) - 2, int(rng() % 9) - 2);
        Polygon input;
        for (auto [x, y] : points) input.emplace_back(x, y);
        check(convex_hull(input));
    }
}

void rectangle_check() {
    using Solver = AreaOfUnionOfRectangles<int, long long>;
    auto check = [](const vector<array<int, 4>> &rectangles) {
        Solver solver;
        vector<int> xs, ys;
        for (auto [l, d, r, u] : rectangles) {
            solver.add_rectangle(l, d, r, u);
            xs.push_back(l);
            xs.push_back(r);
            ys.push_back(d);
            ys.push_back(u);
        }
        sort(xs.begin(), xs.end());
        sort(ys.begin(), ys.end());
        long long expected = 0;
        for (int i = 1; i < int(xs.size()); ++i) for (int j = 1; j < int(ys.size()); ++j) {
            bool covered = false;
            for (auto [l, d, r, u] : rectangles)
                covered |= l <= xs[i - 1] && xs[i] <= r && d <= ys[j - 1] && ys[j] <= u;
            if (covered) expected += (static_cast<long long>(xs[i]) - xs[i - 1]) *
                                    (static_cast<long long>(ys[j]) - ys[j - 1]);
        }
        assert(solver.solve() == expected);
        assert(solver.solve() == expected);
    };
    check({});
    check({{-2000000000, 0, 2000000000, 1}});
    check({{0, -2000000000, 1, 2000000000}});
    check({{-2000000000, -3, 1, 4}, {-1, -2, 2000000000, 5}, {-5, 0, 5, 0}});
    mt19937 rng(17);
    const vector<int> coords{-2000000000, -7, -1, 0, 1, 7, 2000000000};
    for (int tc = 0; tc < 300; ++tc) {
        vector<array<int, 4>> rectangles;
        for (int j = 0; j < 8; ++j) {
            int l = coords[rng() % coords.size()], r = coords[rng() % coords.size()];
            int d = int(rng() % 11) - 5, u = int(rng() % 11) - 5;
            if (l > r) swap(l, r);
            if (d > u) swap(d, u);
            rectangles.push_back({l, d, r, u});
        }
        check(rectangles);
    }
}

long long prim(const vector<vector<long long>> &g) {
    int n = g.size();
    if (n == 0) return 0;
    vector<long long> distance(n, LLONG_MAX);
    vector<bool> used(n);
    distance[0] = 0;
    long long result = 0;
    for (int i = 0; i < n; ++i) {
        int v = -1;
        for (int u = 0; u < n; ++u)
            if (!used[u] && (v == -1 || distance[u] < distance[v])) v = u;
        assert(v != -1 && distance[v] != LLONG_MAX);
        used[v] = true;
        result += distance[v];
        for (int u = 0; u < n; ++u) distance[u] = min(distance[u], g[v][u]);
    }
    return result;
}

void manhattan_check() {
    mt19937 rng(37);
    for (int n = 0; n <= 35; ++n) for (int tc = 0; tc < 30; ++tc) {
        vector<long long> x(n), y(n);
        for (int i = 0; i < n; ++i) {
            x[i] = int(rng() % 11) - 5;
            y[i] = tc == 0 ? -x[i] : int(rng() % 11) - 5;
            if (tc == 1) x[i] = y[i] = 0;
        }
        auto edges = manhattanMST(x, y);
        if (n == 0) assert(edges.empty());
        vector<vector<long long>> complete(n, vector<long long>(n));
        auto sparse = vector<vector<long long>>(n, vector<long long>(n, LLONG_MAX));
        for (int u = 0; u < n; ++u) for (int v = 0; v < n; ++v)
            complete[u][v] = abs(x[u] - x[v]) + abs(y[u] - y[v]);
        for (auto [u, v] : edges) {
            assert(0 <= u && u < n && 0 <= v && v < n && u != v);
            sparse[u][v] = sparse[v][u] = complete[u][v];
        }
        assert(prim(complete) == prim(sparse));
    }
}

int main() {
    hull_check();
    contains_convex_check();
    rectangle_check();
    manhattan_check();
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
