#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_sort_range_composite"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;

static const int MOD = 998244353;
#include "../util/fastio.cpp"
#include "../math/modular/modint.cpp"
#include "../datastructure/segmenttree/sortable_segtree.cpp"

struct AffineMonoid {
    using T = array<mint, 2>;
    static T f(T a, T b) { return {a[0] * b[0], a[1] * b[0] + b[1]}; }
    static T e() { return {1, 0}; }
};

int main() {
    Scanner sc;
    Printer pr;
    int n, q;
    sc.read(n, q);
    vector<int> keys(n);
    vector<AffineMonoid::T> values(n);
    for (int i = 0; i < n; ++i) {
        int a, b;
        sc.read(keys[i], a, b);
        values[i] = {a, b};
    }
    SortableSegmentTree<AffineMonoid> seg(keys, values);
    while (q--) {
        int type;
        sc.read(type);
        if (type == 0) {
            int i, key, a, b;
            sc.read(i, key, a, b);
            seg.set(i, key, {a, b});
        } else {
            int l, r;
            sc.read(l, r);
            if (type == 1) {
                int x;
                sc.read(x);
                auto value = seg.fold(l, r);
                pr.println((value[0] * x + value[1]).val);
            } else if (type == 2) {
                seg.sort_ascending(l, r);
            } else {
                seg.sort_descending(l, r);
            }
        }
    }
}
