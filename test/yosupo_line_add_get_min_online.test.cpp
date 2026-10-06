#define PROBLEM "https://judge.yosupo.jp/problem/line_add_get_min"

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
        ll a, b;
        in.read(a, b);
        tree.add_line(a, b);
    }
    while (q--) {
        int type;
        in.read(type);
        if (type == 0) {
            ll a, b;
            in.read(a, b);
            tree.add_line(a, b);
        } else {
            ll x;
            in.read(x);
            out.println(tree.query(x));
        }
    }
}
