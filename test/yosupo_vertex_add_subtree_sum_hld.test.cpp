#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"

#include <vector>
using namespace std;

using ll = long long;

#include "../util/fastio.cpp"
#include "../tree/hld.cpp"
#include "../datastructure/segtree.cpp"

struct SumMonoid {
    using T = ll;
    static T f(T a, T b) { return a + b; }
    static T e() { return 0; }
};

int main() {
    Scanner sc;
    Printer pr;

    int n, q;
    sc.read(n, q);
    vector<ll> a(n);
    for (auto &&x : a) sc.read(x);

    HeavyLightDecomposition hld(n);
    for (int v = 1; v < n; ++v) {
        int p;
        sc.read(p);
        hld.add_edge(p, v);
    }
    hld.build();

    SegmentTree<SumMonoid> seg(n);
    for (int v = 0; v < n; ++v) seg.set(hld.id[v], a[v]);
    seg.build();

    for (int i = 0; i < q; ++i) {
        int t, v;
        sc.read(t, v);
        if (t == 0) {
            ll x;
            sc.read(x);
            int p = hld.id[v];
            seg.update(p, seg[p] + x);
        } else {
            pr.writeln(hld.subtree_query<ll>(v, [&](int l, int r) { return seg.query(l, r); }));
        }
    }
    return 0;
}
