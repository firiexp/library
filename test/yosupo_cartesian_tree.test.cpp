#define PROBLEM "https://judge.yosupo.jp/problem/cartesian_tree"

#include <bits/stdc++.h>

using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../tree/cartesian_tree.cpp"

int main() {
    Scanner sc;
    Printer pr;

    int n;
    sc.read(n);
    vector<long long> a(n);
    for (auto &&x : a) sc.read(x);

    auto [g, root] = CartesianTree(a);
    vector<int> parent(n, -1);
    parent[root] = root;
    for (int v = 0; v < n; ++v) {
        for (auto &&u : g[v]) parent[u] = v;
    }

    for (int i = 0; i < n; ++i) {
        if (i) pr.print(' ');
        pr.print(parent[i]);
    }
    pr.println();
    return 0;
}
