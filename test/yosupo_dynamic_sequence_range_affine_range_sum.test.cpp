#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum"

#include <algorithm>
#include <array>
#include <vector>
using namespace std;

static const int MOD = 998244353;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../util/modint.cpp"
#include "../datastructure/implicit_treap.cpp"

struct AffineSumMonoid {
    using T = array<mint, 2>;
    using L = array<mint, 2>;
    static T f(T a, T b) { return {a[0] + b[0], a[1] + b[1]}; }
    static T g(T a, L b) { return {a[0] * b[0] + a[1] * b[1], a[1]}; }
    static L h(L a, L b) { return {a[0] * b[0], a[1] * b[0] + b[1]}; }
    static T e() { return {0, 0}; }
    static L l() { return {1, 0}; }
};

int main() {
    Scanner sc;
    Printer pr;

    int n, q;
    sc.read(n, q);
    vector<array<mint, 2>> init(n);
    for (int i = 0; i < n; ++i) {
        int a;
        sc.read(a);
        init[i] = {a, 1};
    }

    ImplicitTreap<AffineSumMonoid> tr(init);
    while (q--) {
        int t;
        sc.read(t);
        if (t == 0) {
            int pos, x;
            sc.read(pos, x);
            tr.insert(pos, {x, 1});
        } else if (t == 1) {
            int pos;
            sc.read(pos);
            tr.erase(pos);
        } else if (t == 2) {
            int l, r;
            sc.read(l, r);
            tr.reverse(l, r);
        } else if (t == 3) {
            int l, r, b, c;
            sc.read(l, r, b, c);
            tr.apply(l, r, {b, c});
        } else {
            int l, r;
            sc.read(l, r);
            pr.writeln(tr.fold(l, r)[0].val);
        }
    }
    return 0;
}
