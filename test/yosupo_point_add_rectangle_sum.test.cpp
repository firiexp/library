#define PROBLEM "https://judge.yosupo.jp/problem/point_add_rectangle_sum"

#include <algorithm>
#include <vector>

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../datastructure/point_add_rectangle_sum.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int n, q;
    sc.read(n, q);

    PointAddRectangleSum<long long> solver;
    for (int i = 0; i < n; ++i) {
        int x, y;
        long long w;
        sc.read(x, y, w);
        solver.add_point(x, y, w);
    }
    for (int i = 0; i < q; ++i) {
        int t;
        sc.read(t);
        if (t == 0) {
            int x, y;
            long long w;
            sc.read(x, y, w);
            solver.add_point(x, y, w);
        } else {
            int l, d, r, u;
            sc.read(l, d, r, u);
            solver.add_query(l, d, r, u);
        }
    }

    auto ans = solver.solve();
    for (auto x : ans) pr.println(x);
    return 0;
}
