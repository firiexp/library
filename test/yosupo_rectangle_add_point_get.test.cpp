#define PROBLEM "https://judge.yosupo.jp/problem/rectangle_add_point_get"

#include "../util/fastio.cpp"
#include "../datastructure/rectangle_add_point_get.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int n, q;
    sc.read(n, q);

    RectangleAddPointGet<long long> solver;
    for (int i = 0; i < n; ++i) {
        int l, d, r, u;
        long long w;
        sc.read(l, d, r, u, w);
        solver.add_rectangle(l, d, r, u, w);
    }
    for (int i = 0; i < q; ++i) {
        int t;
        sc.read(t);
        if (t == 0) {
            int l, d, r, u;
            long long w;
            sc.read(l, d, r, u, w);
            solver.add_rectangle(l, d, r, u, w);
        } else {
            int x, y;
            sc.read(x, y);
            solver.add_query(x, y);
        }
    }

    auto ans = solver.solve();
    for (auto &&x : ans) pr.writeln(x);
    return 0;
}
