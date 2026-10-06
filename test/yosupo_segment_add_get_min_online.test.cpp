#define PROBLEM "https://judge.yosupo.jp/problem/segment_add_get_min"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include "../util/fastio.cpp"
#include "../datastructure/li_chao_tree.cpp"

int main() {
    Scanner in;
    Printer out;
    int n, q;
    in.read(n, q);
    OnlineLiChaoTree<ll> tree(-1000000000LL, 1000000001LL);
    for (int i = 0; i < n; ++i) {
        ll l, r, a, b;
        in.read(l, r, a, b);
        tree.add_segment(a, b, l, r);
    }
    while (q--) {
        int type;
        in.read(type);
        if (type == 0) {
            ll l, r, a, b;
            in.read(l, r, a, b);
            tree.add_segment(a, b, l, r);
        } else {
            ll x;
            in.read(x);
            ll value = tree.query(x);
            if (value == numeric_limits<ll>::max() / 4) out.println("INFINITY");
            else out.println(value);
        }
    }
}
