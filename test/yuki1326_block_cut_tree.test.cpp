#define PROBLEM "https://yukicoder.me/problems/no/1326"

#include <algorithm>
#include <vector>

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../graph/block_cut_tree.cpp"
#include "../tree/hld.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int n, m;
    sc.read(n, m);

    BlockCutTree g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        sc.read(u, v);
        --u, --v;
        g.add_edge(u, v);
    }

    g.build();
    HeavyLightDecomposition hld(g.tree);
    hld.build();

    vector<int> pref((int)g.tree.size());
    for (int i = 0; i < (int)g.tree.size(); ++i) {
        int v = hld.id_inv[i];
        pref[v] = (g.rev[v] != -1);
        if (hld.par[v] != -1) pref[v] += pref[hld.par[v]];
    }

    int q;
    sc.read(q);
    while (q--) {
        int x, y;
        sc.read(x, y);
        --x, --y;
        if (x == y) {
            pr.println(0);
            continue;
        }
        int u = g.id[x], v = g.id[y];
        int a = hld.lca(u, v);
        int ans = pref[u] + pref[v] - 2 * pref[a] + (g.rev[a] != -1);
        if (g.is_articulation[x]) --ans;
        if (g.is_articulation[y]) --ans;
        pr.println(ans);
    }
    return 0;
}
