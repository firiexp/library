#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_range_contour_sum_on_tree"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../tree/range_contour_sum.cpp"

int main() {
    Scanner in;
    Printer out;
    int n, q;
    in.read(n, q);
    vector<long long> values(n);
    for (auto &x : values) in.read(x);
    vector<vector<int>> g(n);
    for (int i = 1; i < n; ++i) {
        int u, v;
        in.read(u, v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    RangeContourSum solver(g, values);
    while (q--) {
        int type, v;
        in.read(type, v);
        if (type == 0) {
            long long x;
            in.read(x);
            solver.add(v, x);
        } else {
            int l, r;
            in.read(l, r);
            out.println(solver.query(v, l, r));
        }
    }
}
