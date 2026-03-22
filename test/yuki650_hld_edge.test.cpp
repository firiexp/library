#define PROBLEM "https://yukicoder.me/problems/no/650"

#include <array>
#include <limits>
#include <vector>
using namespace std;

static const int MOD = 1000000007;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
template<class T> constexpr T INF = numeric_limits<T>::max() / 32 * 15 + 208;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../util/modint.cpp"
#include "../tree/hld_edge.cpp"
#include "../datastructure/segtree.cpp"

struct MatMonoidL {
    using T = array<mint, 4>;
    static T f(T a, T b) {
        return {
            a[0] * b[0] + a[1] * b[2],
            a[0] * b[1] + a[1] * b[3],
            a[2] * b[0] + a[3] * b[2],
            a[2] * b[1] + a[3] * b[3]
        };
    }
    static T e() { return {1, 0, 0, 1}; }
};

struct MatMonoidR {
    using T = array<mint, 4>;
    static T f(T b, T a) {
        return {
            a[0] * b[0] + a[1] * b[2],
            a[0] * b[1] + a[1] * b[3],
            a[2] * b[0] + a[3] * b[2],
            a[2] * b[1] + a[3] * b[3]
        };
    }
    static T e() { return {1, 0, 0, 1}; }
};

int main() {
    Scanner sc;
    Printer pr;

    int n;
    sc.read(n);
    HeavyLightDecompositionEdge hld(n);
    vector<pair<int, int>> edges(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        sc.read(a, b);
        edges[i] = {a, b};
        hld.add_edge(a, b);
    }
    hld.build();

    SegmentTree<MatMonoidL> segl(n);
    SegmentTree<MatMonoidR> segr(n);

    vector<int> child(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        auto [a, b] = edges[i];
        child[i] = (hld.parent(a) == b ? a : b);
        int p = hld.edge_index(child[i]);
        segl.set(p, MatMonoidL::e());
        segr.set(p, MatMonoidR::e());
    }
    segl.build();
    segr.build();

    auto ql = [&](int l, int r) { return segl.query(l, r); };
    auto qr = [&](int l, int r) { return segr.query(l, r); };
    auto merge = [&](MatMonoidL::T a, MatMonoidL::T b) -> MatMonoidL::T {
        return MatMonoidL::f(a, b);
    };

    int q;
    sc.read(q);
    for (int qi = 0; qi < q; ++qi) {
        char type;
        sc.read(type);
        if (type == 'x') {
            int i, x00, x01, x10, x11;
            sc.read(i, x00, x01, x10, x11);
            int p = hld.edge_index(child[i]);
            array<mint, 4> mat = {x00, x01, x10, x11};
            segl.update(p, mat);
            segr.update(p, mat);
        } else {
            int i, j;
            sc.read(i, j);
            auto ans = hld.path_query_ordered(i, j, MatMonoidL::e(), ql, qr, merge);
            pr.println(ans[0].val, ans[1].val, ans[2].val, ans[3].val);
        }
    }
    return 0;
}
