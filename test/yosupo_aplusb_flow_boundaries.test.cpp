#define STANDALONE

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

template<bool Directed, class Flow>
void check_flow_state(const Flow &mf, const vector<tuple<int, int, long long>> &input,
                      int s, int t, long long value, bool complete) {
    int n = mf.G.size();
    auto edges = mf.edges();
    assert(edges.size() == input.size());
    vector<long long> balance(n);
    vector<vector<int>> residual(n);
    for(int id = 0; id < int(input.size()); ++id) {
        auto [u, v, cap] = input[id];
        auto e = mf.get_edge(id);
        assert(e.from == u && e.to == v && e.capacity == cap);
        assert(edges[id].from == u && edges[id].to == v);
        assert(edges[id].capacity == cap && edges[id].flow == e.flow);
        assert((Directed ? 0 : -cap) <= e.flow && e.flow <= cap);
        if(u == v) assert(e.flow == 0);
        balance[u] += e.flow;
        balance[v] -= e.flow;
        if(e.flow < cap) residual[u].push_back(v);
        if(e.flow > (Directed ? 0 : -cap)) residual[v].push_back(u);
    }
    for(int v = 0; v < n; ++v)
        assert(balance[v] == (v == s ? value : v == t ? -value : 0));
    vector<char> reachable(n, false);
    vector<int> pending{s};
    reachable[s] = true;
    for(size_t i = 0; i < pending.size(); ++i) {
        for(int v : residual[pending[i]]) if(!reachable[v]) {
            reachable[v] = true;
            pending.push_back(v);
        }
    }
    assert(mf.min_cut(s) == reachable);
    assert(bool(reachable[t]) == !complete);
    if(complete) {
        long long cut = 0;
        for(auto [u, v, cap] : input) {
            if(reachable[u] && !reachable[v]) cut += cap;
            if(!Directed && reachable[v] && !reachable[u]) cut += cap;
        }
        assert(cut == value);
    }
}

template<bool Directed>
void maxflow_check(bool wide = false) {
    mt19937_64 rng(65 + Directed + 2 * wide);
    for (int tc = 0; tc < 300; ++tc) {
        int n = 2 + rng() % 6;
        vector<tuple<int, int, long long>> edges;
        for (int i = 0; i < 20; ++i)
            edges.push_back({int(rng() % n), int(rng() % n),
                             (long long)(rng() % (wide ? 1000000000001LL : 8))});
        long long expected = LLONG_MAX;
        for (int mask = 0; mask < (1 << n); ++mask) {
            if (!(mask & 1) || (mask >> (n - 1) & 1)) continue;
            long long cut = 0;
            for (auto [u, v, cap] : edges) {
                if ((mask >> u & 1) && !(mask >> v & 1)) cut += cap;
                if (!Directed && (mask >> v & 1) && !(mask >> u & 1)) cut += cap;
            }
            expected = min(expected, cut);
        }
        for (long long limit : {0LL, 1LL, 3LL, expected / 2, expected, LLONG_MAX}) {
            Dinic<long long, Directed> dinic(n);
            CostScalingDinic<long long, Directed> scaling(n);
            for (int id = 0; id < int(edges.size()); ++id) {
                auto [u, v, cap] = edges[id];
                assert(dinic.add_edge(u, v, cap) == id);
                assert(scaling.add_edge(u, v, cap) == id);
            }
            check_flow_state<Directed>(dinic, edges, 0, n - 1, 0, expected == 0);
            check_flow_state<Directed>(scaling, edges, 0, n - 1, 0, expected == 0);
            auto di = dinic.G;
            auto si = scaling.G;
            check_residual(dinic.G, di);
            check_residual(scaling.G, si);
            long long first = min<long long>(expected, limit);
            assert(dinic.flow(0, n - 1, limit) == first);
            assert(scaling.flow(0, n - 1, limit) == first);
            check_flow_state<Directed>(dinic, edges, 0, n - 1, first, first == expected);
            check_flow_state<Directed>(scaling, edges, 0, n - 1, first, first == expected);
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
            check_flow_state<Directed>(dinic, edges, 0, n - 1, expected, true);
            check_flow_state<Directed>(scaling, edges, 0, n - 1, expected, true);
            check_residual(dinic.G, di);
            check_residual(scaling.G, si);
            assert(dinic.flow(0, n - 1) == 0);
            assert(scaling.flow(0, n - 1) == 0);
        }
    }
    for (int limit : {0, 1, 3, 10, 11}) {
        CostScalingDinic<int, Directed> g(2);
        g.add_edge(0, 1, 10);
        assert(g.flow(0, 1, limit) == min(limit, 10));
        assert(g.flow(0, 1) == 10 - min(limit, 10));
    }
    for (long long cap : {1LL << 31, 1LL << 32, (1LL << 32) + 7, 1LL << 40, 1000000000000LL}) {
        CostScalingDinic<long long, Directed> g(2);
        g.add_edge(0, 0, cap);
        g.add_edge(0, 1, 0);
        g.add_edge(0, 1, cap);
        auto initial = g.G;
        assert(g.flow(0, 1) == cap);
        check_residual(g.G, initial);
        assert(g.flow(0, 1) == 0);
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

template<bool Directed>
void scaling_width_check() {
    CostScalingDinic<long long, Directed> empty(4);
    assert(empty.flow(0, 3) == 0);
    empty.add_edge(0, 3, 0);
    assert(empty.flow(0, 3) == 0);
    for(long long cap : {1LL, 2LL, 3LL, (1LL << 60) - 1, 1LL << 60}) {
        CostScalingDinic<long long, Directed> g(4);
        g.add_edge(0, 0, cap);
        g.add_edge(0, 1, cap);
        g.add_edge(1, 3, cap);
        auto initial = g.G;
        assert(g.flow(0, 3, 0) == 0);
        assert(g.flow(0, 3, cap / 2) == cap / 2);
        assert(g.flow(0, 3) == cap - cap / 2);
        assert(g.flow(3, 0) == (Directed ? cap : 2 * cap));
        check_residual(g.G, initial);
    }
    CostScalingDinic<long long, Directed> changed(2);
    changed.add_edge(0, 1, 1);
    changed.G[0][0].cap = 1LL << 40;
    assert(changed.flow(0, 1) == (1LL << 40));
    CostScalingDinic<long long, true> largest(2);
    largest.add_edge(0, 1, LLONG_MAX);
    assert(largest.flow(0, 1, LLONG_MAX) == LLONG_MAX);
}

template<class Flow>
void shortest_layer_check() {
    Flow g(70);
    for(int v = 1; v <= 32; ++v) {
        g.add_edge(0, v, 1);
        g.add_edge(v, 69, 1);
        g.add_edge(v, v, 5);
    }
    g.add_edge(0, 33, 100);
    for(int v = 33; v < 68; ++v) g.add_edge(v, v + 1, 100);
    auto initial = g.G;
    assert(g.flow(0, 69, 0) == 0);
    assert(g.flow(0, 69, 7) == 7);
    assert(g.flow(0, 69, 25) == 25);
    assert(g.flow(0, 69) == 0);
    check_residual(g.G, initial);
    assert(g.flow(69, 0, 32) == 32);
    assert(g.flow(0, 69, 32) == 32);
    check_residual(g.G, initial);
    Flow disconnected(4);
    disconnected.add_edge(0, 1, 7);
    disconnected.add_edge(2, 3, 9);
    assert(disconnected.flow(0, 3) == 0);
}

template<template<class, bool> class Flow, bool Directed>
void edge_api_check() {
    Flow<long long, Directed> g(2);
    vector<tuple<int, int, long long>> input;
    check_flow_state<Directed>(g, input, 0, 1, 0, true);
    input = {{0, 0, 4}, {0, 1, 0}, {1, 0, 5}, {0, 1, 3}, {0, 1, 2}};
    for(int id = 0; id < int(input.size()); ++id) {
        auto [u, v, c] = input[id];
        assert(g.add_edge(u, v, c) == id);
    }
    long long forward = Directed ? 5 : 10;
    assert(g.flow(0, 1) == forward);
    check_flow_state<Directed>(g, input, 0, 1, forward, true);
    assert(g.add_edge(0, 1, 7) == int(input.size()));
    input.emplace_back(0, 1, 7);
    assert(g.flow(0, 1) == 7);
    check_flow_state<Directed>(g, input, 0, 1, forward + 7, true);
    long long backward = Directed ? 5 : forward + 7;
    assert(g.flow(1, 0) == forward + 7 + backward);
    check_flow_state<Directed>(g, input, 1, 0, backward, true);
    const auto copied = g;
    check_flow_state<Directed>(copied, input, 1, 0, backward, true);
    Flow<short, false> narrow(2);
    int reversed = narrow.add_edge(1, 0, 10);
    assert(narrow.flow(0, 1) == 10);
    assert(narrow.get_edge(reversed).flow == -10);
    Flow<unsigned long long, true> wide(2);
    int id = wide.add_edge(0, 1, ULLONG_MAX);
    assert(wide.flow(0, 1, ULLONG_MAX) == ULLONG_MAX);
    assert(wide.get_edge(id).capacity == ULLONG_MAX);
    assert(wide.get_edge(id).flow == ULLONG_MAX);
    assert(wide.flow(1, 0, ULLONG_MAX) == ULLONG_MAX);
    assert(wide.get_edge(id).flow == 0);
}

int main() {
    maxflow_check<true>();
    maxflow_check<false>();
    maxflow_check<true>(true);
    maxflow_check<false>(true);
    scaling_width_check<true>();
    scaling_width_check<false>();
    shortest_layer_check<Dinic<long long, true>>();
    shortest_layer_check<Dinic<long long, false>>();
    shortest_layer_check<CostScalingDinic<long long, true>>();
    shortest_layer_check<CostScalingDinic<long long, false>>();
    edge_api_check<Dinic, true>();
    edge_api_check<Dinic, false>();
    edge_api_check<CostScalingDinic, true>();
    edge_api_check<CostScalingDinic, false>();
    mincost_check();
}
