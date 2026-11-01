#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
template<class T> constexpr T INF = numeric_limits<T>::max() / 32 * 15 + 208;
#include "../flow/dinic.cpp"
#include "../flow/costscalingdinic.cpp"

template<template<class, bool> class Flow, bool Directed>
void check() {
    Flow<long long, Directed> empty(0);
    empty.reset_flow();
    assert(empty.edges().empty());
    mt19937 rng(335);
    for(int tc = 0; tc < 300; ++tc) {
        int n = 2 + rng() % 7;
        Flow<long long, Directed> g(n), fresh(n);
        vector<pair<int, int>> positions;
        for(int id = 0; id < 25; ++id) {
            int u = rng() % n, v = rng() % n;
            positions.emplace_back(u, g.G[u].size());
            assert(g.add_edge(u, v, rng() % 10) == id);
        }
        g.flow(0, n - 1);
        for(int id = 0; id < 25; ++id) {
            long long cap = rng() % 20;
            long long f = rng() % (cap + 1);
            if(!Directed && rng() % 2) f = -f;
            auto [u, index] = positions[id];
            int v = g.G[u][index].to;
            g.change_edge(id, cap, f);
            auto e = g.get_edge(id);
            assert(e.from == u && e.to == v && e.capacity == cap && e.flow == f);
            auto &forward = g.G[u][index];
            auto &reverse = g.G[v][forward.rev];
            assert(forward.cap == cap - f);
            assert(reverse.cap == (Directed ? f : cap + f));
            assert(reverse.to == u && reverse.rev == index);
            assert(fresh.add_edge(u, v, cap) == id);
        }
        vector<const void *> storage;
        for(const auto &adj : g.G) storage.push_back(adj.data());
        g.reset_flow();
        g.reset_flow();
        for(int v = 0; v < n; ++v) {
            assert(g.G[v].data() == storage[v]);
            for(int i = 0; i < int(g.G[v].size()); ++i)
                assert(g.G[v][i].cap == fresh.G[v][i].cap);
        }
        for(auto e : g.edges()) assert(e.flow == 0);
        assert(g.flow(0, n - 1) == fresh.flow(0, n - 1));
        g.reset_flow();
        fresh.reset_flow();
        assert(g.flow(n - 1, 0) == fresh.flow(n - 1, 0));
        int id = g.add_edge(0, n - 1, 3);
        assert(id == 25);
        g.change_edge(id, 4, 0);
        assert(g.get_edge(id).capacity == 4);
    }
    Flow<long long, Directed> path(3);
    int a = path.add_edge(0, 1, 0), b = path.add_edge(1, 2, 0);
    for(long long cap : {7LL, 1LL << 40, 2LL, 0LL}) {
        path.change_edge(a, cap, cap / 2);
        path.change_edge(b, cap, cap / 2);
        assert(path.flow(0, 2) == cap - cap / 2);
        path.reset_flow();
        assert(path.flow(0, 2) == cap);
    }
    if constexpr(!Directed) {
        path.change_edge(a, 7, -3);
        path.change_edge(b, 7, -3);
        assert(path.flow(2, 0) == 4);
        assert(path.get_edge(a).flow == -7);
    }
    Flow<unsigned long long, true> wide(2);
    int id = wide.add_edge(0, 1, 0);
    wide.change_edge(id, ULLONG_MAX, ULLONG_MAX - 1);
    assert(wide.flow(0, 1, ULLONG_MAX) == 1);
    assert(wide.get_edge(id).flow == ULLONG_MAX);
    wide.reset_flow();
    assert(wide.flow(0, 1, ULLONG_MAX) == ULLONG_MAX);
}

int main() {
    check<Dinic, true>();
    check<Dinic, false>();
    check<CostScalingDinic, true>();
    check<CostScalingDinic, false>();
}
