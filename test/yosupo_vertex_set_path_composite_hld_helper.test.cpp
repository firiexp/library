#define PROBLEM "https://judge.yosupo.jp/problem/vertex_set_path_composite"

#include <array>
#include <limits>
#include <vector>
using namespace std;

static const int MOD = 998244353;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
template<class T> constexpr T INF = ::numeric_limits<T>::max() / 32 * 15 + 208;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../util/modint.cpp"
#include "../tree/hld.cpp"
#include "../datastructure/segmenttree/segtree.cpp"

struct Ml {
    using T = array<mint, 2>;
    static T f(T a, T b) { return {a[0] * b[0], a[1] * b[0] + b[1]}; }
    static T e() { return {1, 0}; }
};

struct Mr {
    using T = array<mint, 2>;
    static T f(T b, T a) { return {a[0] * b[0], a[1] * b[0] + b[1]}; }
    static T e() { return {1, 0}; }
};

int main() {
    Scanner sc;
    Printer pr;

    int n, q;
    sc.read(n, q);
    HeavyLightDecomposition hld(n);
    SegmentTree<Ml> segl(n);
    SegmentTree<Mr> segr(n);

    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) sc.read(a[i], b[i]);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        sc.read(u, v);
        hld.add_edge(u, v);
    }
    hld.build();
    for (int i = 0; i < n; ++i) {
        int p = hld.id[i];
        segl.set(p, {a[i], b[i]});
        segr.set(p, {a[i], b[i]});
    }
    segl.build();
    segr.build();

    auto ql = [&](int l, int r) { return segl.query(l, r); };
    auto qr = [&](int l, int r) { return segr.query(l, r); };
    auto merge = [&](Ml::T x, Ml::T y) -> Ml::T { return {x[0] * y[0], x[1] * y[0] + y[1]}; };

    for (int i = 0; i < q; ++i) {
        int t, p, c, d;
        sc.read(t, p, c, d);
        if (t == 0) {
            int v = hld.id[p];
            segl.update(v, {c, d});
            segr.update(v, {c, d});
        } else {
            auto val = hld.path_query_ordered(p, c, Ml::e(), ql, qr, merge, false);
            pr.println((val[0] * d + val[1]).val);
        }
    }
    return 0;
}
