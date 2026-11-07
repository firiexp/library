#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include "../util/fastio.cpp"
#include "../geometry/convex_hull.cpp"
#include "../geometry/furthest_pair.cpp"

__int128 distance_squared(IntPoint a, IntPoint b) {
    __int128 dx = a.x;
    __int128 dy = a.y;
    dx -= b.x;
    dy -= b.y;
    return dx * dx + dy * dy;
}

void check(const vector<IntPoint> &points) {
    const auto original = points;
    auto [i, j] = furthest_pair(points);
    int n = points.size();
    assert(0 <= i && i < n && 0 <= j && j < n && i != j);
    __int128 best = 0;
    for (int u = 0; u < n; ++u)
        for (int v = u + 1; v < n; ++v)
            best = max(best, distance_squared(points[u], points[v]));
    assert(distance_squared(points[i], points[j]) == best);
    assert(points == original);
    auto ids = convex_hull_indices(points);
    vector<IntPoint> hull;
    for (int id : ids) hull.push_back(points[id]);
    int h = hull.size();
    for (int start = 0; start < h; ++start) {
        const auto original_hull = hull;
        auto [u, v] = furthest_pair_convex(hull);
        if (h < 2) {
            assert(u == -1 && v == -1);
        } else {
            assert(0 <= u && u < h && 0 <= v && v < h && u != v);
            assert(distance_squared(hull[u], hull[v]) == best);
            assert(distance_squared(points[ids[u]], points[ids[v]]) == best);
            assert(ids[u] != ids[v]);
        }
        assert(hull == original_hull);
        rotate(hull.begin(), hull.begin() + 1, hull.end());
        rotate(ids.begin(), ids.begin() + 1, ids.end());
    }
}

void check_furthest_pair() {
    assert(furthest_pair_convex({}) == make_pair(-1, -1));
    assert(furthest_pair_convex({{3, 4}}) == make_pair(-1, -1));
    mt19937_64 rng(20261007);
    for (int mask = 1; mask < (1 << 9); ++mask) {
        vector<IntPoint> points;
        for (int i = 0; i < 9; ++i)
            if (mask >> i & 1) points.emplace_back(i % 3, i / 3);
        if (points.size() > 1) check(points);
        points.push_back(points[0]);
        points.push_back(points[0]);
        shuffle(points.begin(), points.end(), rng);
        check(points);
    }
    check({{40, 880}, {350, 80}, {450, 130}, {750, 300},
           {315, 164}, {940, 770}, {897, 663}, {850, 790}});
    check({{4, -7}, {4, -2}, {4, 0}, {4, 9}});
    check({{-7, 4}, {-2, 4}, {0, 4}, {9, 4}});
    check({{0, -4}, {3, -2}, {3, 2}, {0, 4}, {-3, 2}, {-3, -2}});
    check({{0, 0}, {6, 0}, {6, 2}, {0, 2}});
    for (int tc = 0; tc < 3000; ++tc) {
        vector<IntPoint> points(2 + rng() % 40);
        for (auto &[x, y] : points) {
            x = int(rng() % 101) - 50;
            y = int(rng() % 101) - 50;
            if (tc % 10 == 0) x = y = 3;
            if (tc % 10 == 1) y = 3 * x + 7;
        }
        check(points);
    }
    const ll limit = 1000000000000000000LL;
    check({{-limit, -limit}, {limit, -limit}, {limit, limit}, {-limit, limit}});
    check({{-limit, -limit}, {-limit + 1, -limit}, {limit, limit - 1}, {limit, limit}});
    check({{-limit, -limit}, {0, 0}, {limit, limit}, {limit, limit}});
    check({{limit, limit}, {limit, limit}});
    const vector<ll> coords{-limit, -limit + 1, -4000000000LL, -1, 0, 1, 4000000000LL, limit - 1, limit};
    for (int tc = 0; tc < 500; ++tc) {
        vector<IntPoint> points(2 + rng() % 30);
        for (auto &[x, y] : points) {
            x = coords[rng() % coords.size()];
            y = coords[rng() % coords.size()];
        }
        check(points);
    }
}

int main() {
    check_furthest_pair();
}
