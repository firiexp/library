#define PROBLEM "https://judge.yosupo.jp/problem/vertex_set_path_composite"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
const int MOD = 998244353;
#include "../util/fastio.cpp"
#include "../math/modular/modint.cpp"
#include "../tree/hld.cpp"
#include "../datastructure/segmenttree/segtree.cpp"

struct Affine {
    using T = array<mint, 2>;
    static T f(T a, T b) { return {a[0] * b[0], a[1] * b[0] + b[1]}; }
    static T e() { return {1, 0}; }
};

struct ReverseAffine : Affine {
    static T f(T a, T b) { return Affine::f(b, a); }
};

int main() {
    Scanner in;
    Printer out;
    int n, q;
    in.read(n, q);
    vector<Affine::T> values(n);
    for (auto &f : values) {
        int a, b;
        in.read(a, b);
        f = {a, b};
    }
    HeavyLightDecomposition hld(n);
    for (int i = 1; i < n; ++i) {
        int u, v;
        in.read(u, v);
        hld.add_edge(u, v);
    }
    hld.build();
    SegmentTree<Affine> forward(n);
    SegmentTree<ReverseAffine> backward(n);
    for (int v = 0; v < n; ++v) {
        forward.set(hld.id[v], values[v]);
        backward.set(hld.id[v], values[v]);
    }
    forward.build();
    backward.build();
    while (q--) {
        int type, u, v, x;
        in.read(type, u, v, x);
        if (type == 0) {
            forward.update(hld.id[u], {v, x});
            backward.update(hld.id[u], {v, x});
        } else {
            auto result = Affine::e();
            hld.path_ordered(u, v, [&](int l, int r, bool reversed) {
                result = Affine::f(result, reversed ? backward.query(l, r) : forward.query(l, r));
            });
            out.println((result[0] * x + result[1]).val);
        }
    }
}
