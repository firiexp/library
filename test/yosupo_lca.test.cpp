#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include <bits/stdc++.h>

using namespace std;

template<class T> constexpr T INF = ::numeric_limits<T>::max() / 32 * 15 + 208;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../tree/LCA.cpp"

int main() {
    Scanner sc;
    Printer pr;

    int n, q;
    sc.read(n, q);
    LCA lca(n);
    for (int v = 1; v < n; ++v) {
        int p;
        sc.read(p);
        lca.add_edge(p, v);
    }
    lca.build(0);

    while (q--) {
        int u, v;
        sc.read(u, v);
        pr.writeln(lca.lca(u, v));
    }
    return 0;
}
