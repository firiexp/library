#define PROBLEM "https://judge.yosupo.jp/problem/jump_on_tree"

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../tree/link_cut_tree.cpp"

struct Monoid {
    using T = int;
    static T f(T, T) { return 0; }
    static T e() { return 0; }
};

int main() {
    Scanner sc;
    Printer pr;
    int n, q;
    sc.read(n, q);
    LinkCutTree<Monoid> lct(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        sc.read(u, v);
        lct.link(u, v);
    }
    while (q--) {
        int u, v, k;
        sc.read(u, v, k);
        pr.println(lct.jump(u, v, k));
    }
}
