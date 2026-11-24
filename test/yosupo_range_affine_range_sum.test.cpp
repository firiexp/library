#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"

#include <cassert>
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

#include <charconv>
#include "../util/fastio.cpp"
#include "../datastructure/segmenttree/lazysegtree.cpp"
#include "../math/modular/modint.cpp"

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
    vector<Monoid::T> values(n, {0, 1});
    for (auto &value : values) in.read(value[0]);
    LazySegmentTree<Monoid> seg(values);
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
