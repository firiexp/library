#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include "../util/fastio.cpp"
#include "../tree/hld.cpp"
#include "../datastructure/segmenttree/lazysegtree.cpp"

struct SumAdd {
    using T = array<ll, 2>;
    using L = ll;
    static T f(T a, T b) { return {a[0] + b[0], a[1] + b[1]}; }
    static T g(T a, L x) { return {a[0] + a[1] * x, a[1]}; }
    static L h(L a, L b) { return a + b; }
    static T e() { return {0, 0}; }
    static L l() { return 0; }
};

void self_check() {
    mt19937 rng(155);
    for (int tc = 0; tc < 350; ++tc) {
        int n = 1 + rng() % 28;
        HeavyLightDecomposition hld(n);
        vector<vector<int>> g(n);
        for (int v = 1; v < n; ++v) {
            if (tc % 2 && rng() % 4 == 0) continue;
            int p = tc % 5 == 0 ? v - 1 : tc % 5 == 1 ? 0 : rng() % v;
            hld.add_edge(p, v);
            g[p].push_back(v);
            g[v].push_back(p);
        }
        vector<int> seen(n), roots;
        for (int v = 0; v < n; ++v) if (!seen[v]) {
            vector<int> component{v};
            seen[v] = 1;
            for (int i = 0; i < (int)component.size(); ++i) {
                for (int u : g[component[i]]) if (!seen[u]) {
                    seen[u] = 1;
                    component.push_back(u);
                }
            }
            roots.push_back(component[rng() % component.size()]);
        }
        shuffle(roots.begin(), roots.end(), rng);
        hld.build(roots);
        auto ids = hld.id, parents = hld.par, depths = hld.dep;
        const auto& index = hld;
        vector<ll> values(n);
        LazySegmentTree<SumAdd> seg(n);
        for (int v = 0; v < n; ++v) seg.set(hld.id[v], {0, 1});
        seg.build();
        for (int root = 0; root < n; ++root) {
            vector<int> parent(n, -2), depth(n), order{root};
            parent[root] = -1;
            for (int i = 0; i < (int)order.size(); ++i) {
                int v = order[i];
                for (int u : g[v]) if (u != parent[v]) {
                    parent[u] = v;
                    depth[u] = depth[v] + 1;
                    order.push_back(u);
                }
            }
            for (int v : order) {
                vector<int> expected, actual;
                for (int u : order) {
                    int x = u;
                    while (x != -1 && x != v) x = parent[x];
                    if (x == v) expected.push_back(u);
                }
                int calls = 0, previous = -1;
                index.rerooted_subtree(v, root, [&](int l, int r) {
                    assert(0 <= l && l < r && r <= n && previous <= l);
                    previous = r;
                    ++calls;
                    for (int i = l; i < r; ++i) actual.push_back(hld.id_inv[i]);
                });
                sort(expected.begin(), expected.end());
                sort(actual.begin(), actual.end());
                assert(actual == expected && 1 <= calls && calls <= 2);
                ll add = int(rng() % 11) - 5;
                index.rerooted_subtree(v, root, [&](int l, int r) { seg.update(l, r, add); });
                for (int u : expected) values[u] += add;
                ll sum = 0, oracle = 0;
                index.rerooted_subtree(v, root, [&](int l, int r) { sum += seg.query(l, r)[0]; });
                for (int u : expected) oracle += values[u];
                assert(sum == oracle);
                for (int u : order) {
                    int a = u, b = v;
                    while (depth[a] > depth[b]) a = parent[a];
                    while (depth[b] > depth[a]) b = parent[b];
                    while (a != b) { a = parent[a]; b = parent[b]; }
                    assert(index.rerooted_lca(u, v, root) == a);
                }
            }
        }
        assert(hld.id == ids && hld.par == parents && hld.dep == depths);
        for (int v = 0; v < n; ++v) assert(seg.query(hld.id[v], hld.id[v] + 1)[0] == values[v]);
    }
}

int main() {
    self_check();
}
