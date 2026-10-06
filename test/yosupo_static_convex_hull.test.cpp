#define PROBLEM "https://judge.yosupo.jp/problem/static_convex_hull"

#include <algorithm>
#include <cassert>
#include <climits>
#include <random>
#include <set>
#include <vector>
using namespace std;
using ll = long long;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include <charconv>
#include "../util/fastio.cpp"
#include "../geometry/convex_hull.cpp"

vector<IntPoint> brute_hull(vector<IntPoint> points) {
    using Wide = __int128;
    sort(points.begin(), points.end());
    points.erase(unique(points.begin(), points.end()), points.end());
    if (points.size() <= 2) return points;
    auto turn = [](IntPoint a, IntPoint b, IntPoint c) -> Wide {
        return (Wide(b.first) - a.first) * (Wide(c.second) - a.second) -
               (Wide(b.second) - a.second) * (Wide(c.first) - a.first);
    };
    auto distance_squared = [](IntPoint a, IntPoint b) -> Wide {
        Wide x = Wide(b.first) - a.first, y = Wide(b.second) - a.second;
        return x * x + y * y;
    };
    vector<IntPoint> hull;
    IntPoint current = points[0];
    do {
        hull.push_back(current);
        IntPoint next = points[0] == current ? points[1] : points[0];
        for (auto p : points) {
            Wide cross = turn(current, next, p);
            if (cross < 0 || (cross == 0 && distance_squared(current, p) > distance_squared(current, next)))
                next = p;
        }
        current = next;
    } while (current != hull[0]);
    return hull;
}

void self_check() {
    auto check = [](const vector<IntPoint> &points) {
        assert(convex_hull(points) == brute_hull(points));
    };
    check({});
    check({{0, 0}});
    check({{0, 0}, {0, 0}});
    check({{INT_MIN, INT_MAX}, {INT_MAX, INT_MIN}});
    check({{-2000000000, -2000000000}, {2000000000, -2000000000},
           {2000000000, 2000000000}, {-2000000000, 2000000000}});
    check({{INT_MIN, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MAX}, {INT_MIN, INT_MAX}});
    check({{INT_MIN, INT_MIN}, {0, 0}, {INT_MAX, INT_MAX}, {0, 0}});
    const ll limit = 1000000000000000000LL;
    check({{-limit, -limit}, {limit, -limit}, {limit, limit}, {-limit, limit}});
    check({{-limit, -limit}, {-limit + 1, -limit}, {limit, limit - 1}, {limit, limit}});
    check({{-limit, -limit}, {0, 0}, {limit, limit}, {limit, limit}});
    mt19937 rng(18);
    const vector<ll> coords{-limit, -limit + 1, INT_MIN, -2000000000, -1, 0, 1,
                            2000000000, INT_MAX, limit - 1, limit};
    for (int tc = 0; tc < 500; ++tc) {
        vector<IntPoint> points(rng() % 30);
        for (auto &[x, y] : points) {
            x = tc % 2 ? ll(rng()) + INT_MIN : coords[rng() % coords.size()];
            y = tc % 2 ? ll(rng()) + INT_MIN : coords[rng() % coords.size()];
        }
        check(points);
    }
}

int main() {
    self_check();
    Scanner sc;
    Printer pr;
    int t;
    sc.read(t);
    while (t--) {
        int n;
        sc.read(n);
        vector<IntPoint> ps(n);
        for (int i = 0; i < n; ++i) {
            sc.read(ps[i].first, ps[i].second);
        }
        auto ch = convex_hull(ps);
        pr.println((int)ch.size());
        for (auto [x, y] : ch) pr.println(x, y);
    }
    return 0;
}
