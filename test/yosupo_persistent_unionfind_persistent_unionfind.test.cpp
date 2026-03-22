#define PROBLEM "https://judge.yosupo.jp/problem/persistent_unionfind"

#include <bits/stdc++.h>

using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../datastructure/persistent_unionfind.cpp"

int main() {
    Scanner sc;
    Printer pr;

    int n, q;
    sc.read(n, q);

    PersistentUnionFind uf(n);
    for (int i = 0; i < q; ++i) {
        int t, k, u, v;
        sc.read(t, k, u, v);
        ++k;
        if (t == 0) {
            uf.unite(k, u, v);
        } else {
            pr.println(uf.same(k, u, v));
            uf.copy_version(k);
        }
    }
    return 0;
}
