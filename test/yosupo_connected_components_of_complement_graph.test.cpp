#define PROBLEM "https://judge.yosupo.jp/problem/connected_components_of_complement_graph"

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../graph/complement_components.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int n, m;
    sc.read(n, m);
    vector<vector<int>> g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        sc.read(u, v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    auto components = complement_components(g);
    pr.println(components.size());
    for (const auto &component : components) {
        pr.print(component.size());
        for (int v : component) {
            pr.print(' ');
            pr.print(v);
        }
        pr.print('\n');
    }
}
