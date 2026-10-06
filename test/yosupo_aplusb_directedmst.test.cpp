#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include "../util/fastio.cpp"
#include "../graph/chu_liu_edmonds.cpp"

ll brute_cost(const ChuLiuEdmonds<ll> &g) {
    vector<vector<int>> incoming(g.n);
    for (int i = 0; i < int(g.edges.size()); ++i) {
        const auto &e = g.edges[i];
        if (e.from != e.to) incoming[e.to].push_back(i);
    }
    vector<int> parent(g.n, g.root);
    ll best = LLONG_MAX;
    auto enumerate = [&](auto &&self, int v, ll cost) -> void {
        if (v == g.n) {
            for (int u = 0; u < g.n; ++u) {
                int x = u;
                for (int step = 0; step < g.n && x != g.root; ++step) x = parent[x];
                if (x != g.root) return;
            }
            best = min(best, cost);
            return;
        }
        if (v == g.root) {
            self(self, v + 1, cost);
            return;
        }
        for (int i : incoming[v]) {
            parent[v] = g.edges[i].from;
            self(self, v + 1, cost + g.edges[i].cost);
        }
    };
    enumerate(enumerate, 0, 0);
    return best;
}

void check(const ChuLiuEdmonds<ll> &g, ll expected) {
    auto res = g.solve();
    auto again = g.solve();
    assert(res.exists == again.exists && res.cost == again.cost);
    assert(res.parent == again.parent && res.edge_id == again.edge_id);
    assert(res.exists == (expected != LLONG_MAX));
    if (!res.exists) {
        assert(res.cost == 0 && res.parent.empty() && res.edge_id.empty());
        return;
    }
    assert(res.cost == expected);
    assert(int(res.parent.size()) == g.n && int(res.edge_id.size()) == g.n);
    assert(res.parent[g.root] == g.root && res.edge_id[g.root] == -1);
    ll cost = 0;
    for (int v = 0; v < g.n; ++v) {
        if (v == g.root) continue;
        int id = res.edge_id[v];
        assert(0 <= id && id < int(g.edges.size()));
        const auto &e = g.edges[id];
        assert(e.to == v && e.from == res.parent[v]);
        cost += e.cost;
        int x = v;
        for (int step = 0; step < g.n && x != g.root; ++step) x = res.parent[x];
        assert(x == g.root);
    }
    assert(cost == res.cost);
}

void check_directedmst() {
    check(ChuLiuEdmonds<ll>(1, 0), 0);
    for (int shape = 0; shape < 3; ++shape) {
        ChuLiuEdmonds<ll> g(65, 64);
        for (int v = 0; v < 64; ++v) {
            int p = shape == 0 ? 64 : shape == 1 ? v + 1 : (v + 65) / 2;
            g.add_edge(p, v, 1);
        }
        check(g, 64);
    }
    for (bool disconnected : {false, true}) {
        ChuLiuEdmonds<ll> g(65, 64);
        for (int v = 0; v < 64; v += 2) {
            g.add_edge(v, v + 1, -1);
            g.add_edge(v + 1, v, -1);
            g.add_edge(v, v, -100);
            if (!disconnected || v != 62) {
                g.add_edge(64, v, 10);
                g.add_edge(64, v, 10);
            }
        }
        check(g, disconnected ? LLONG_MAX : 32 * 9);
    }
    ChuLiuEdmonds<ll> nested(5, 4);
    for (auto [u, v, c] : vector<array<int, 3>>{
             {0, 1, -2}, {1, 0, -2}, {2, 3, -2}, {3, 2, -2},
             {1, 2, -1}, {3, 0, -1}, {4, 0, 5}, {4, 2, 5}}) {
        nested.add_edge(u, v, c);
    }
    check(nested, brute_cost(nested));
    mt19937 rng(20261006);
    for (int tc = 0; tc < 1000; ++tc) {
        int n = 1 + rng() % 6;
        ChuLiuEdmonds<ll> g(n, rng() % n);
        int m = rng() % 21;
        for (int i = 0; i < m; ++i) {
            int u = rng() % n, v = rng() % n;
            g.add_edge(u, v, int(rng() % 9) - 4);
        }
        check(g, brute_cost(g));
    }
}

int main() {
    check_directedmst();
    Scanner in;
    Printer out;
    int a, b;
    in.read(a, b);
    out.println(a + b);
}
