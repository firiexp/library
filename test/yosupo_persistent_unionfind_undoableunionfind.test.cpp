#define PROBLEM "https://judge.yosupo.jp/problem/persistent_unionfind"

#include <bits/stdc++.h>

using namespace std;

#include "../util/fastio.cpp"
#include "../datastructure/undoableunionfind.cpp"

int main() {
    Scanner sc;
    Printer pr;

    int n, q;
    sc.read(n, q);
    using A = array<int, 4>;
    vector<vector<A>> g(q + 1);
    vector<int> ans(q + 1, -1);
    for (int i = 1; i <= q; ++i) {
        int t, k, u, v;
        sc.read(t, k, u, v);
        ++k;
        g[k].push_back({t, i, u, v});
    }

    UndoableUnionFind uf(n);
    auto dfs = [&](auto &&f, A cur) -> void {
        int t = cur[0], idx = cur[1], u = cur[2], v = cur[3];
        if (t == 1) {
            ans[idx] = uf.same(u, v);
            return;
        }
        if (t == 0) uf.unite(u, v);
        for (auto &&nxt : g[idx]) f(f, nxt);
        if (t == 0) uf.undo();
    };
    dfs(dfs, A{-1, 0, -1, -1});

    for (int i = 1; i <= q; ++i) {
        if (ans[i] != -1) pr.writeln(ans[i]);
    }
    return 0;
}
