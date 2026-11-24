#define PROBLEM "https://judge.yosupo.jp/problem/jump_on_tree"

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../tree/hld.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int n, q;
    sc.read(n, q);
    HeavyLightDecomposition hld(n);
    for (int i = 1; i < n; ++i) {
        int u, v;
        sc.read(u, v);
        hld.add_edge(u, v);
    }
    hld.build();
    while (q--) {
        int u, v, k;
        sc.read(u, v, k);
        pr.println(hld.jump(u, v, k));
    }
}
