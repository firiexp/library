#define PROBLEM "https://judge.yosupo.jp/problem/rectangle_sum"

#include "../util/fastio.cpp"
#include "../datastructure/static_rectangle_sum.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int n, q;
    sc.read(n, q);

    StaticRectangleSum<long long> solver;
    for (int i = 0; i < n; ++i) {
        int x, y;
        long long w;
        sc.read(x, y, w);
        solver.add_point(x, y, w);
    }
    for (int i = 0; i < q; ++i) {
        int l, d, r, u;
        sc.read(l, d, r, u);
        solver.add_query(l, d, r, u);
    }

    auto ans = solver.solve();
    for (auto x : ans) pr.writeln(x);
    return 0;
}
