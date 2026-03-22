#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"

#include <array>
#include <vector>

static const int MOD = 998244353;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../datastructure/segmenttree/lazysegtree.cpp"
#include "../util/modint.cpp"

struct Monoid{
    using T = array<mint, 2>;
    using L = array<mint, 2>;
    static T f(T a, T b) { return {a[0]+b[0], a[1]+b[1]}; }
    static T g(T a, L b) {
        return {a[0] * b[0] + a[1] * b[1], a[1]};
    }
    static L h(L a, L b) {
        return {a[0]*b[0], a[1]*b[0]+b[1]};
    }
    static T e() { return {0, 0}; }
    static L l() { return {1, 0}; }
};
int main() {
    Scanner in;
    Printer out;

    int n, q;
    in.read(n, q);
    vector<int> v(n);
    for (auto &&i : v) in.read(i);
    LazySegmentTree<Monoid> seg(n);
    for (int i = 0; i < n; ++i) seg.set(i, {v[i], 1});
    seg.build();
    for (int i = 0; i < q; ++i) {
        int t;
        in.read(t);
        if(!t){
            int l, r, b, c;
            in.read(l, r, b, c);
            seg.update(l, r, {b, c});
        }else {
            int l, r;
            in.read(l, r);
            out.println(seg.query(l, r)[0].val);
        }
    }
    return 0;
}
