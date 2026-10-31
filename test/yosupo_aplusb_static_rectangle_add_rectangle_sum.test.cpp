#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using uint = unsigned;
constexpr int MOD = 998244353;
#include "../util/fastio.cpp"
#include "../math/modular/modint.cpp"
#include "../datastructure/range_query_2d/static_rectangle_add_rectangle_sum.cpp"

struct Rectangle {
    int l, d, r, u;
    long long w;
};

template<class T>
void check(const vector<Rectangle>& rects, const vector<Rectangle>& queries) {
    StaticRectangleAddRectangleSum<T> solver;
    vector<T> expected;
    for (auto q : queries) {
        solver.add_query(q.l, q.d, q.r, q.u);
        T sum = 0;
        for (auto r : rects) {
            long long width = max(0LL, (long long)min(q.r, r.r) - max(q.l, r.l));
            long long height = max(0LL, (long long)min(q.u, r.u) - max(q.d, r.d));
            sum += T(r.w) * T(width) * T(height);
        }
        expected.push_back(sum);
    }
    for (auto r : rects) solver.add_rectangle(r.l, r.d, r.r, r.u, T(r.w));
    const auto& view = solver;
    assert(view.solve() == expected);
    assert(view.solve() == expected);
    solver.add_query(0, 0, 0, 0);
    expected.push_back(T(0));
    assert(solver.solve() == expected);
}

template<class T>
void self_check() {
    check<T>({}, {});
    check<T>({}, {{0, 0, 3, 4, 0}});
    check<T>({{0, 0, 2, 3, 5}}, {});
    check<T>({{0, 0, 2, 3, 5}}, {{0, 0, 2, 3, 0}, {1, 1, 3, 4, 0}, {2, 0, 4, 3, 0}, {0, 3, 2, 4, 0}});
    check<T>({{0, 0, 0, 3, 5}, {-3, 1, 5, 1, -7}}, {{-10, -10, 10, 10, 0}});
    check<T>({{-3, -4, 5, 6, 7}, {-3, -4, 5, 6, 7}, {-1, -2, 3, 4, -5}},
             {{-3, -4, 5, 6, 0}, {-1, -2, 3, 4, 0}, {-3, -2, 3, 6, 0}, {0, 0, 0, 5, 0}});
    mt19937 rng(76);
    for (int tc = 0; tc < 2000; ++tc) {
        vector<Rectangle> rects, queries;
        int n = rng() % 20, q = rng() % 20;
        for (int i = 0; i < n + q; ++i) {
            int l = (int)(rng() % 21) - 10, r = (int)(rng() % 21) - 10;
            int d = (int)(rng() % 21) - 10, u = (int)(rng() % 21) - 10;
            if (l > r) swap(l, r);
            if (d > u) swap(d, u);
            Rectangle rect{l, d, r, u, (int)(rng() % 41) - 20};
            (i < n ? rects : queries).push_back(rect);
        }
        check<T>(rects, queries);
    }
}

int main() {
    self_check<long long>();
    self_check<__int128>();
    self_check<mint>();
    vector<Rectangle> rects = {{INT_MIN, INT_MIN, INT_MAX, INT_MAX, 7}, {INT_MIN, -1, 0, INT_MAX, -3}, {-1, -1, 1, 1, -11}};
    vector<Rectangle> queries = {{INT_MIN, INT_MIN, INT_MAX, INT_MAX, 0}, {INT_MIN, INT_MIN, INT_MIN + 1, INT_MIN + 1, 0}, {INT_MAX - 1, INT_MAX - 1, INT_MAX, INT_MAX, 0}, {-1, -1, 1, 1, 0}};
    check<__int128>(rects, queries);
    check<mint>(rects, queries);
}
