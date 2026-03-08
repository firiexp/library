#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_point_get"

#include <vector>
using namespace std;

static const int MOD = 998244353;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;

#include "../util/fastio.cpp"
#include "../util/modint.cpp"
#include "../datastructure/dualsegtree.cpp"

struct Monoid {
    using T = pair<mint, mint>;
    static T f(T a, T b) {
        return {b.first * a.first, b.first * a.second + b.second};
    }
    static T e() { return {1, 0}; }
};

int main() {
    Scanner sc;
    Printer pr;

    int n, q;
    sc.read(n, q);
    vector<mint> a(n);
    for (int i = 0; i < n; ++i) {
        int x;
        sc.read(x);
        a[i] = x;
    }

    DualSegmentTree<Monoid> seg(n);
    while (q--) {
        int t;
        sc.read(t);
        if (t == 0) {
            int l, r, b, c;
            sc.read(l, r, b, c);
            seg.update(l, r, {b, c});
        } else {
            int i;
            sc.read(i);
            auto [mul, add] = seg[i];
            pr.writeln((mul * a[i] + add).val);
        }
    }
    return 0;
}
