#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
#include "../util/fastio.cpp"
#include "../util/modint_base.cpp"
#include "../datastructure/point_add_rectangle_sum.cpp"

template<class T>
void check(bool modular) {
    const vector<int> coords = {-1000000000, -16777217, -1, 0, 1, 16777215, 16777216, 16777217, 1000000000};
    mt19937 rng(63);
    for (int tc = 0; tc < 100; ++tc) {
        PointAddRectangleSum<T> solver;
        vector<tuple<int, int, ll>> points;
        vector<T> expected;
        assert(solver.solve().empty());
        for (int step = 0; step < 100; ++step) {
            auto coord = [&]() { return coords[rng() % coords.size()]; };
            if (rng() % 2) {
                int x = coord(), y = coord();
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
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
