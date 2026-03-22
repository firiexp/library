#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <numeric>
#include <bitset>
#include <cmath>

static const int MOD = 1000000007;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
using namespace std;

template<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;

#include "../datastructure/segmenttree/persistent_segtree.cpp"

struct Monoid{
    using T = long long;
    static T f(T a, T b) { return a + b; }
    static T e() { return 0; }
};

int main() {
    int n, q;
    cin >> n >> q;
    vector<ll> a(n);
    for (auto &&i : a) scanf("%lld", &i);

    PersistentSegmentTree<Monoid> seg(a);
    for (int i = 0; i < q; ++i) {
        int t, x, y;
        scanf("%d %d %d", &t, &x, &y);
        if(t == 0) seg.add(x, y);
        else printf("%lld\n", seg.query(x, y));
    }
    return 0;
}
