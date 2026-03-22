#define PROBLEM "https://judge.yosupo.jp/problem/frequency_table_of_tree_distance"

#include <bits/stdc++.h>

using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../tree/frequency_table_of_tree_distance.cpp"

int main() {
    Scanner sc;
    Printer pr;

    int n;
    sc.read(n);
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        sc.read(u, v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    auto ans = frequency_table_of_tree_distance(g);
    for (int d = 1; d < n; ++d) {
        if (d != 1) pr.print(' ');
        pr.print(ans[d]);
    }
    pr.println();
    return 0;
}
