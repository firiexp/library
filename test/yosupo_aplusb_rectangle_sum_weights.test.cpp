#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
#include "../util/fastio.cpp"
#include "../math/modular/modint_base.cpp"
#include "../datastructure/range_query_2d/fenwick_tree_2d.cpp"
#include "../datastructure/range_query_2d/point_add_rectangle_sum.cpp"
#include "../datastructure/range_query_2d/fenwick_tree_2d.cpp"

template<class T>
void check(bool modular) {
    PointAddRectangleSum<T> dense;
    for (int w = -15; w <= 16; ++w) dense.add_point(3, 4, T(w));
    assert(dense.solve().empty());
    dense.add_query(3, 4, 4, 5);
    dense.add_point(3, 4, T(-20));
    dense.add_point(-2, 1, T(7));
    dense.add_query(-2, 1, 4, 5);
    assert((dense.solve() == vector<T>{T(16), T(3)}));

    const vector<int> coords = {-1000000000, -16777217, -1, 0, 1, 16777215, 16777216, 16777217, 1000000000};
    mt19937 rng(63);
    for (int tc = 0; tc < 100; ++tc) {
        PointAddRectangleSum<T> solver;
        vector<tuple<int, int, ll>> points;
        vector<T> expected;
        assert(solver.solve().empty());
        const int prefix_lengths[] = {0, 4, 64, 100};
        int prefix = prefix_lengths[tc / 4 % 4];
        for (int step = 0; step < 100; ++step) {
            auto coord = [&]() { return coords[rng() % coords.size()]; };
            bool update = step < prefix || (step > prefix && (prefix == 0 ? step % 2 : rng() % 2));
            if (update) {
                int x = coord(), y = coord();
                if (tc % 4 == 1 || tc % 4 == 3) x = -1;
                if (tc % 4 == 2 || tc % 4 == 3) y = 0;
                ll w = int(rng() % 21) - 10;
                if (modular) w += (int(rng() % 3) - 1LL) * 998244353;
                solver.add_point(x, y, T(w));
                points.emplace_back(x, y, w);
            } else {
                int l = coord(), r = coord(), d = coord(), u = coord();
                if (l > r) swap(l, r);
                if (d > u) swap(d, u);
                solver.add_query(l, d, r, u);
                ll sum = 0;
                for (auto [x, y, w] : points)
                    if (l <= x && x < r && d <= y && y < u) sum += w;
                expected.push_back(T(sum));
            }
            if (step % 25 == 0) assert(solver.solve() == expected);
        }
        assert(solver.solve() == expected);
        assert(solver.solve() == expected);
    }
}

int main() {
    PointAddRectangleSum<ll> repeated;
    repeated.add_query(-2, 3, -1, 4);
    vector<ll> expected{0};
    ll total = 0;
    for (ll w : {3, -5, 0, 9}) {
        repeated.add_point(-2, 3, w);
        repeated.add_query(-2, 3, -1, 4);
        total += w;
        expected.push_back(total);
        assert(repeated.solve() == expected);
    }
    assert(repeated.solve() == expected);
    PointAddRectangleSum<modint<998244353>> modular;
    modular.add_point(0, 0, 1);
    modular.add_query(0, 0, 1, 1);
    assert(modular.solve() == vector<modint<998244353>>{1});
    PointAddRectangleSum<float> floating;
    floating.add_point(0, 16777216, 1.0f);
    floating.add_query(0, 16777216, 1, 16777217);
    assert(floating.solve() == vector<float>{1.0f});
    check<modint<998244353>>(true);
    check<float>(false);
    check<long long>(false);
}
