#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"
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

template<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;

#include "../util/modint.cpp"

#include "../datastructure/segtree.cpp"

struct Monoid{
    using T = array<mint, 2>;
    static T f(T a, T b) { return {a[0]*b[0], a[1]*b[0]+b[1]}; }
    static T e() { return {1, 0}; }
};

int main() {
    int n, q;
    cin >> n >> q;
    SegmentTree<Monoid> seg(n);
    for (int i = 0; i < n; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        seg.set(i, {a, b});
    }
    seg.build();
    for (int i = 0; i < q; ++i) {
        int a, b, c, d;
        scanf("%d %d %d %d", &a, &b, &c, &d);
        if(!a) seg.update(b, {c, d});
        else {
            auto ans = seg.query(b, c);
            printf("%d\n", (ans[0]*d+ans[1]).val);
        }
    }
    return 0;
}