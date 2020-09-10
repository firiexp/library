#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <numeric>
#include <bitset>
#include <cmath>

static const int MOD = 998244353;
using ll = long long;
using u32 = unsigned;
using u64 = unsigned long long;
using namespace std;
#include "../datastructure/lazysegtree.cpp"
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
    int n, q;
    cin >> n >> q;
    vector<int> v(n);
    for (auto &&i : v) scanf("%d", &i);
    LazySegmentTree<Monoid> seg(n);
    for (int i = 0; i < n; ++i) seg.set(i, {v[i], 1});
    seg.build();
    for (int i = 0; i < q; ++i) {
        int t;
        scanf("%d", &t);
        if(!t){
            int l, r, b, c;
            scanf("%d %d %d %d\n", &l, &r, &b, &c);
            seg.update(l, r, {b, c});
        }else {
            int l, r;
            scanf("%d %d", &l, &r);
            printf("%d\n", seg.query(l, r)[0].val);
        }
    }
    return 0;
}