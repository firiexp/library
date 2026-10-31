#define PROBLEM "https://judge.yosupo.jp/problem/persistent_range_affine_range_sum"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
static constexpr int MOD = 998244353;
#include "../util/fastio.cpp"
#include "../math/modular/modint.cpp"
#include "../datastructure/segmenttree/persistent_lazy_segtree.cpp"

struct AffineSum {
    using T = array<mint, 2>;
    using L = array<mint, 2>;
    static T f(T a, T b) { return {a[0] + b[0], a[1] + b[1]}; }
    static T g(T a, L b) { return {a[0] * b[0] + a[1] * b[1], a[1]}; }
    static L h(L a, L b) { return {a[0] * b[0], a[1] * b[0] + b[1]}; }
    static T e() { return {0, 0}; }
    static L l() { return {1, 0}; }
};

int main() {
    Scanner in;
    Printer out;
    int n, q;
    in.read(n, q);
    vector<AffineSum::T> values(n);
    for (auto &value : values) {
        int a;
        in.read(a);
        value = {a, 1};
    }
    PersistentLazySegmentTree<AffineSum> seg(values);
    vector<int> versions(q + 1);
    for (int i = 0; i < q; ++i) {
        int type, k, l, r;
        in.read(type, k);
        if (type == 0) {
            int b, c;
            in.read(l, r, b, c);
            versions[i + 1] = seg.update(versions[k + 1], l, r, {b, c});
        } else if (type == 1) {
            int s;
            in.read(s, l, r);
            versions[i + 1] = seg.copy_range(versions[k + 1], versions[s + 1], l, r);
        } else {
            in.read(l, r);
            out.println(seg.query(versions[k + 1], l, r)[0].val);
        }
    }
}
