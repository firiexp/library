#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
template<class T> constexpr T INF = numeric_limits<T>::max() / 32 * 15 + 208;
#include "../util/fastio.cpp"
#include "../flow/dinic.cpp"
#include "../flow/costscalingdinic.cpp"
#include "../flow/primaldual.cpp"

template<class G>
void check_residual(const G &g, const G &initial) {
    assert(g.size() == initial.size());
    for (int v = 0; v < int(g.size()); ++v) {
        assert(g[v].size() == initial[v].size());
        for (int i = 0; i < int(g[v].size()); ++i) {
            const auto &e = g[v][i];
            assert(0 <= e.to && e.to < int(g.size()));
            assert(0 <= e.rev && e.rev < int(g[e.to].size()));
            assert(e.to != v || e.rev != i);
            const auto &r = g[e.to][e.rev];
            assert(r.to == v && r.rev == i);
            assert(e.cap >= 0);
            assert(e.cap + r.cap == initial[v][i].cap + initial[e.to][e.rev].cap);
        }
    }
}

template<bool Directed>
void maxflow_check() {
    mt19937 rng(65 + Directed);
    for (int tc = 0; tc < 300; ++tc) {
        int n = 2 + rng() % 6;
        vector<array<int, 3>> edges;
        for (int i = 0; i < 20; ++i)
            edges.push_back({int(rng() % n), int(rng() % n), int(rng() % 8)});
        int expected = INT_MAX;
        for (int mask = 0; mask < (1 << n); ++mask) {
            if (!(mask & 1) || (mask >> (n - 1) & 1)) continue;
            int cut = 0;
            for (auto [u, v, cap] : edges) {
                if ((mask >> u & 1) && !(mask >> v & 1)) cut += cap;
                if (!Directed && (mask >> v & 1) && !(mask >> u & 1)) cut += cap;
            }
            expected = min(expected, cut);
        }
        for (long long limit : {0LL, 1LL, 3LL, 10LL, 11LL, LLONG_MAX}) {
            Dinic<long long, Directed> dinic(n);
            CostScalingDinic<long long, Directed> scaling(n);
            for (auto [u, v, cap] : edges) {
                dinic.add_edge(u, v, cap);
                scaling.add_edge(u, v, cap);
            }
            auto di = dinic.G;
            auto si = scaling.G;
            check_residual(dinic.G, di);
            check_residual(scaling.G, si);
            long long first = min<long long>(expected, limit);
            assert(dinic.flow(0, n - 1, limit) == first);
            assert(scaling.flow(0, n - 1, limit) == first);
            check_residual(dinic.G, di);
            check_residual(scaling.G, si);
            if (limit == 0) {
                for (int v = 0; v < n; ++v) {
                    for (int i = 0; i < int(di[v].size()); ++i) assert(dinic.G[v][i].cap == di[v][i].cap);
                    for (int i = 0; i < int(si[v].size()); ++i) assert(scaling.G[v][i].cap == si[v][i].cap);
                }
            }
            assert(dinic.flow(0, n - 1) == expected - first);
            assert(scaling.flow(0, n - 1) == expected - first);
            check_residual(dinic.G, di);
            check_residual(scaling.G, si);
            assert(dinic.flow(0, n - 1) == 0);
            assert(scaling.flow(0, n - 1) == 0);
        }
    }
    for (int limit : {0, 1, 3, 10, 11}) {
        CostScalingDinic<long long, Directed> g(2);
        g.add_edge(0, 1, 10);
        assert(g.flow(0, 1, limit) == min(limit, 10));
        assert(g.flow(0, 1) == 10 - min(limit, 10));
    }
}

void mincost_check() {
    mt19937 rng(20261003);
    for (int tc = 0; tc < 300; ++tc) {
        int n = 2 + rng() % 4;
        vector<array<int, 4>> edges;
        for (int i = 0; i < 6; ++i)
            edges.push_back({int(rng() % n), int(rng() % n), int(rng() % 3), int(rng() % 6)});
        vector<int> best(13, INT_MAX), balance(n);
        auto enumerate = [&](auto &&self, int i, int cost) -> void {
            if (i == int(edges.size())) {
                for (int v = 1; v < n - 1; ++v) if (balance[v] != 0) return;
                if (balance[0] < 0 || balance[0] != -balance[n - 1]) return;
                best[balance[0]] = min(best[balance[0]], cost);
                return;
            }
            auto [u, v, cap, c] = edges[i];
            for (int f = 0; f <= cap; ++f) {
                balance[u] += f;
                balance[v] -= f;
                self(self, i + 1, cost + f * c);
                balance[u] -= f;
                balance[v] += f;
            }
        };
        enumerate(enumerate, 0, 0);
        for (int amount = 0; amount < int(best.size()); ++amount) {
            PrimalDual<int, int> g(n);
            for (auto [u, v, cap, cost] : edges) g.add_edge(u, v, cap, cost);
            auto initial = g.G;
            check_residual(g.G, initial);
            int ok = -1;
            int cost = g.flow(0, n - 1, amount, ok);
            assert(ok == (best[amount] != INT_MAX));
            if (ok) assert(cost == best[amount]);
            check_residual(g.G, initial);
            for (const auto &adj : g.G)
                for (const auto &e : adj) assert(e.cost == -g.G[e.to][e.rev].cost);
        }
    }
}

int main() {
    maxflow_check<true>();
    maxflow_check<false>();
    mincost_check();
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
