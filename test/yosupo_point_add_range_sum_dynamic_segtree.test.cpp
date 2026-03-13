#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include <vector>
using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../datastructure/dynamic_segtree.cpp"

struct Monoid{
    using T = long long;
    static T f(T a, T b) { return a + b; }
    static T e() { return 0; }
};

int main() {
    Scanner sc;
    Printer pr;

    int n, q;
    sc.read(n, q);
    DynamicSegmentTree<Monoid> seg(n);
    if (n > 0) seg.reserve((size_t)4 * n);
    for (int i = 0; i < n; ++i) {
        long long a;
        sc.read(a);
        seg.add(i, a);
    }

    while (q--) {
        int t;
        sc.read(t);
        if (t == 0) {
            int p;
            long long x;
            sc.read(p, x);
            seg.add(p, x);
        } else {
            int l, r;
            sc.read(l, r);
            pr.writeln(seg.query(l, r));
        }
    }
    return 0;
}
