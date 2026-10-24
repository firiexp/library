#define STANDALONE

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
        return (Wide(b.x) - a.x) * (Wide(c.y) - a.y) -
               (Wide(b.y) - a.y) * (Wide(c.x) - a.x);
    };
    auto distance_squared = [](IntPoint a, IntPoint b) -> Wide {
        Wide x = Wide(b.x) - a.x, y = Wide(b.y) - a.y;
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

int brute_contains(const vector<IntPoint> &hull, IntPoint p) {
    if (hull.empty()) return 0;
    if (hull.size() == 1) return hull[0] == p ? 1 : 0;
    bool boundary = false;
    for (size_t i = 0; i < hull.size(); ++i) {
        auto a = hull[i], b = hull[(i + 1) % hull.size()];
        __int128 area = (__int128(b.x) - a.x) * (__int128(p.y) - a.y) -
                        (__int128(b.y) - a.y) * (__int128(p.x) - a.x);
        if (area < 0) return 0;
        if (area == 0 && min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
            min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y)) boundary = true;
    }
    return boundary ? 1 : hull.size() == 2 ? 0 : 2;
}

void self_check() {
    mt19937 query_rng(282);
    auto check = [&](const vector<IntPoint> &points) {
        const auto hull = convex_hull(points);
        assert(hull == brute_hull(points));
        vector<IntPoint> queries = points;
        for (size_t i = 0; i < hull.size(); ++i) {
            auto a = hull[i], b = hull[(i + 1) % hull.size()];
            queries.emplace_back(ll((__int128(a.x) + b.x) / 2), ll((__int128(a.y) + b.y) / 2));
        }
        for (int i = 0; i < 50; ++i)
            queries.emplace_back(int(query_rng() % 41) - 20, int(query_rng() % 41) - 20);
        for (auto p : queries) assert(contains_convex(hull, p) == brute_contains(hull, p));
    };
    check({});
    check({{0, 0}});
    check({{0, 0}, {0, 0}});
    check({{0, 0}, {6, 0}, {6, 6}, {0, 6}});
    check({{0, 0}, {2, 0}, {0, 2}});
    const vector<IntPoint> square{{0, 0}, {6, 0}, {6, 6}, {0, 6}};
    for (auto p : vector<IntPoint>{{0, 0}, {3, 0}, {0, 3}, {6, 3}, {3, 6}})
        assert(contains_convex(square, p) == 1);
    for (auto p : vector<IntPoint>{{3, 3}, {2, 3}, {3, 2}})
        assert(contains_convex(square, p) == 2);
    for (auto p : vector<IntPoint>{{7, 0}, {0, 7}, {-1, 0}, {0, -1}, {7, 7}})
        assert(contains_convex(square, p) == 0);
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
    for (int tc = 0; tc < 1000; ++tc) {
        vector<IntPoint> points(rng() % 30);
        for (auto &[x, y] : points) {
            x = tc % 3 == 0 ? int(rng() % 41) - 20 : tc % 3 == 1 ? ll(rng()) + INT_MIN : coords[rng() % coords.size()];
            y = tc % 3 == 0 ? int(rng() % 41) - 20 : tc % 3 == 1 ? ll(rng()) + INT_MIN : coords[rng() % coords.size()];
        }
        check(points);
    }
}

int main() {
    self_check();
}
