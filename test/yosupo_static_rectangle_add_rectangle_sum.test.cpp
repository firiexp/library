#define PROBLEM "https://judge.yosupo.jp/problem/static_rectangle_add_rectangle_sum"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using uint = unsigned;
constexpr int MOD = 998244353;
#include "../util/fastio.cpp"
#include "../math/modular/modint.cpp"
#include "../datastructure/range_query_2d/static_rectangle_add_rectangle_sum.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int n, q;
    sc.read(n, q);
    StaticRectangleAddRectangleSum<mint> solver;
    for (int i = 0; i < n; ++i) {
        int l, d, r, u, w;
        sc.read(l, d, r, u, w);
        solver.add_rectangle(l, d, r, u, mint(w));
    }
    for (int i = 0; i < q; ++i) {
        int l, d, r, u;
        sc.read(l, d, r, u);
        solver.add_query(l, d, r, u);
    }
    for (auto x : solver.solve()) pr.println(x.val);
}
