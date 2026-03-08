#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite"
#include <bits/stdc++.h>

static const int MOD = 998244353;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
using namespace std;

#include "../util/modint.cpp"
#include "../tree/link_cut_tree.cpp"

struct Monoid {
    using T = array<mint, 2>;
    static T f(T a, T b) { return {a[0] * b[0], a[1] * b[0] + b[1]}; }
    static T e() { return {1, 0}; }
};

int main() {
    int n, q;
    cin >> n >> q;
    LinkCutTree<Monoid> lct(n);
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        lct.set(i, {a, b});
    }
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        lct.link(u, v);
    }
    for (int i = 0; i < q; ++i) {
        int t;
        cin >> t;
        if (t == 0) {
            int u, v, w, x;
            cin >> u >> v >> w >> x;
            lct.cut(u, v);
            lct.link(w, x);
        } else if (t == 1) {
            int p, c, d;
            cin >> p >> c >> d;
            lct.set(p, {c, d});
        } else {
            int u, v, x;
            cin >> u >> v >> x;
            auto f = lct.fold(u, v);
            cout << (f[0] * x + f[1]).val << '\n';
        }
    }
    return 0;
}
