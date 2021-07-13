#define PROBLEM "https://judge.yosupo.jp/problem/vertex_set_path_composite"
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <bitset>

static const int MOD = 998244353;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
using namespace std;

template<class T> constexpr T INF = ::numeric_limits<T>::max() / 32 * 15 + 208;

#include "../util/modint.cpp"

#include "../tree/hld.cpp"

#include "../datastructure/segtree.cpp"

struct Ml {
    using T = array<mint, 2>;
    static T f(T a, T b) { return {a[0]*b[0], a[1]*b[0]+b[1]}; }
    static T e() { return {1, 0}; }
};

struct Mr {
    using T = array<mint, 2>;
    static T f(T b, T a) { return {a[0]*b[0], a[1]*b[0]+b[1]}; }
    static T e() { return {1, 0}; }
};

int main() {
    int n, q;
    cin >> n >> q;
    HeavyLightDecomposition G(n);
    SegmentTree<Ml> segl(n);
    SegmentTree<Mr> segr(n);
    {
        vector<int> a(n), b(n);
        for (int i = 0; i < n; ++i) {
            scanf("%d %d", &a[i], &b[i]);
        }
        for (int i = 0; i < n - 1; ++i) {
            int l, r;
            scanf("%d %d", &l, &r);
            G.add_edge(l, r);
        }
        G.build();
        for (int i = 0; i < n; ++i) {
            int id = G.id[i];
            segl.set(id, {a[i], b[i]});
            segr.set(id, {a[i], b[i]});
        }
        segl.build(); segr.build();
    }
    auto fl = [&](int l, int r){ return segl.query(l, r); };
    auto fr = [&](int l, int r){ return segr.query(l, r); };
    auto merge = [&](Ml::T a, Ml::T b) -> Ml::T { return {a[0]*b[0], a[1]*b[0]+b[1]}; };
    for (int i = 0; i < q; ++i) {
        int t, a, b, c;
        scanf("%d %d %d %d", &t, &a, &b, &c);
        if(t == 0){
            a = G.id[a];
            segl.update(a, {b, c});
            segr.update(a, {b, c});
        }else {
            auto val = G.query_order(a, b, Ml::e(), fl, fr, merge, false);
            printf("%d\n", (val[0]*c + val[1]).val);
        }
    }
    return 0;
}