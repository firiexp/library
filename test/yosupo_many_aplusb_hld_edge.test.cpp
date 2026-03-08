#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb"

#include <algorithm>
#include <array>
#include <limits>
#include <random>
#include <utility>
#include <vector>
using namespace std;

using ll = long long;

#include "../util/fastio.cpp"
#include "../tree/hld_edge.cpp"
#include "../datastructure/segtree.cpp"

struct Ml {
    using T = array<ll, 2>;
    static T f(T a, T b) { return {a[0] * b[0], a[1] * b[0] + b[1]}; }
    static T e() { return {1, 0}; }
};

struct Mr {
    using T = array<ll, 2>;
    static T f(T b, T a) { return {a[0] * b[0], a[1] * b[0] + b[1]}; }
    static T e() { return {1, 0}; }
};

struct Sum {
    using T = ll;
    static T f(T a, T b) { return a + b; }
    static T e() { return 0; }
};

static array<ll, 2> compose(array<ll, 2> a, array<ll, 2> b) {
    return {a[0] * b[0], a[1] * b[0] + b[1]};
}

int main() {
    {
        mt19937 rng(123456789);
        for (int n = 1; n <= 50; ++n) {
            for (int trial = 0; trial < 150; ++trial) {
                vector<vector<int>> g(n);
                for (int v = 1; v < n; ++v) {
                    int p = uniform_int_distribution<int>(0, v - 1)(rng);
                    g[p].push_back(v);
                    g[v].push_back(p);
                }

                vector<int> parent(n, -1), depth(n, 0), order = {0};
                for (int i = 0; i < n; ++i) {
                    int v = order[i];
                    for (auto &&u : g[v]) {
                        if (u == parent[v]) continue;
                        parent[u] = v;
                        depth[u] = depth[v] + 1;
                        order.push_back(u);
                    }
                }

                HeavyLightDecompositionEdge hld(n);
                for (int v = 0; v < n; ++v) {
                    for (auto &&u : g[v]) {
                        if (v < u) hld.add_edge(v, u);
                    }
                }
                hld.build();

                SegmentTree<Ml> segl(n);
                SegmentTree<Mr> segr(n);
                SegmentTree<Sum> segsum(n);
                vector<array<ll, 2>> aff(n, {1, 0});
                vector<ll> weight(n, 0);
                for (int v = 1; v < n; ++v) {
                    aff[v] = {uniform_int_distribution<int>(-3, 3)(rng), uniform_int_distribution<int>(-5, 5)(rng)};
                    weight[v] = uniform_int_distribution<int>(-10, 10)(rng);
                }
                for (int v = 0; v < n; ++v) {
                    int p = hld.edge_index(v);
                    if (p == -1) continue;
                    segl.set(p, aff[v]);
                    segr.set(p, aff[v]);
                    segsum.set(p, weight[v]);
                }
                segl.build();
                segr.build();
                segsum.build();

                auto ql = [&](int l, int r) { return segl.query(l, r); };
                auto qr = [&](int l, int r) { return segr.query(l, r); };
                auto merge = [&](Ml::T x, Ml::T y) -> Ml::T { return compose(x, y); };

                auto lca = [&](int a, int b) {
                    while (depth[a] > depth[b]) a = parent[a];
                    while (depth[b] > depth[a]) b = parent[b];
                    while (a != b) a = parent[a], b = parent[b];
                    return a;
                };

                auto naive_path = [&](int a, int b) {
                    int c = lca(a, b);
                    vector<int> vs;
                    for (int v = a; v != c; v = parent[v]) vs.push_back(v);
                    vector<int> down;
                    for (int v = b; v != c; v = parent[v]) down.push_back(v);
                    reverse(down.begin(), down.end());
                    for (auto &&v : down) vs.push_back(v);
                    array<ll, 2> ret = {1, 0};
                    for (auto &&v : vs) ret = compose(ret, aff[v]);
                    return ret;
                };

                vector<int> tin(n), tout(n);
                int timer = 0;
                auto dfs = [&](auto &&self, int v) -> void {
                    tin[v] = timer++;
                    for (auto &&u : g[v]) {
                        if (u == parent[v]) continue;
                        self(self, u);
                    }
                    tout[v] = timer;
                };
                dfs(dfs, 0);

                auto naive_subtree_sum = [&](int v) {
                    ll ret = 0;
                    for (int u = 0; u < n; ++u) {
                        if (u == v) continue;
                        if (tin[v] <= tin[u] && tin[u] < tout[v]) ret += weight[u];
                    }
                    return ret;
                };

                for (int iter = 0; iter < 200; ++iter) {
                    int type = uniform_int_distribution<int>(0, 2)(rng);
                    if (type == 0 && n >= 2) {
                        int v = uniform_int_distribution<int>(1, n - 1)(rng);
                        aff[v] = {uniform_int_distribution<int>(-3, 3)(rng), uniform_int_distribution<int>(-5, 5)(rng)};
                        weight[v] = uniform_int_distribution<int>(-10, 10)(rng);
                        int p = hld.edge_index(v);
                        segl.update(p, aff[v]);
                        segr.update(p, aff[v]);
                        segsum.update(p, weight[v]);
                    } else if (type == 1) {
                        int a = uniform_int_distribution<int>(0, n - 1)(rng);
                        int b = uniform_int_distribution<int>(0, n - 1)(rng);
                        auto got = hld.path_query_ordered(a, b, Ml::e(), ql, qr, merge);
                        auto expect = naive_path(a, b);
                        if (got != expect) return 1;
                    } else {
                        int v = uniform_int_distribution<int>(0, n - 1)(rng);
                        ll got = hld.subtree_query<ll>(v, [&](int l, int r) { return segsum.query(l, r); });
                        ll expect = naive_subtree_sum(v);
                        if (got != expect) return 1;
                    }
                }
            }
        }
    }

    Scanner sc;
    Printer pr;
    int t;
    sc.read(t);
    while (t--) {
        long long a, b;
        sc.read(a, b);
        pr.writeln(a + b);
    }
    return 0;
}
