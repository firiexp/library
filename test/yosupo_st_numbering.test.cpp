#define PROBLEM "https://judge.yosupo.jp/problem/st_numbering"

#include <bits/stdc++.h>
using namespace std;

#include "../graph/connectivity/st_numbering.cpp"
#include "../util/fastio.cpp"

int main() {
    Scanner in;
    Printer out;
    int cases;
    in.read(cases);
    while (cases--) {
        int n, m, s, t;
        in.read(n, m, s, t);
        vector<vector<int>> g(n);
        for (int i = 0; i < m; ++i) {
            int u, v;
            in.read(u, v);
            g[u].push_back(v);
            g[v].push_back(u);
        }
        auto order = st_numbering(g, s, t);
        if (order.empty()) {
            out.println("No");
            continue;
        }
        vector<int> rank(n);
        for (int i = 0; i < n; ++i) rank[order[i]] = i;
        out.println("Yes");
        out.println(rank);
    }
}
