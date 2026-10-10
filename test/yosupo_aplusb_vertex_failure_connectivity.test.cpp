#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../graph/vertex_failure_connectivity.cpp"

void check(VertexFailureConnectivity &solver, int n, const vector<pair<int, int>> &edges) {
    solver.build();
    vector<vector<int>> g(n);
    for (auto [u, v] : edges) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int x = 0; x < n; ++x) {
        for (int u = 0; u < n; ++u) {
            vector<char> seen(n);
            vector<int> queue;
            if (u != x) seen[u] = 1, queue.push_back(u);
            for (int i = 0; i < (int)queue.size(); ++i) {
                for (int v : g[queue[i]]) {
                    if (v == x || seen[v]) continue;
                    seen[v] = 1;
                    queue.push_back(v);
                }
            }
            for (int v = 0; v < n; ++v)
                assert(solver.connected_without_vertex(u, v, x) == (bool)seen[v]);
        }
    }
}

void check_large(int n, int mode) {
    VertexFailureConnectivity solver(n);
    for (int v = 1; v < n; ++v) {
        if (mode == 3 && v == n / 2) continue;
        solver.add_edge(mode == 1 ? 0 : v - 1, v);
    }
    if (mode == 2) solver.add_edge(n - 1, 0);
    solver.build();
    mt19937 rng(20261010);
    for (int i = 0; i < 100000; ++i) {
        int u = rng() % n, v = rng() % n, x = rng() % n;
        bool expected = u != x && v != x;
        if (mode == 1) expected &= x != 0 || u == v;
        else if (mode != 2) {
            expected &= !(min(u, v) < x && x < max(u, v));
            if (mode == 3) expected &= (u < n / 2) == (v < n / 2);
        }
        assert(solver.connected_without_vertex(u, v, x) == expected);
    }
}

int main() {
    for (int n = 0; n <= 6; ++n) {
        vector<pair<int, int>> possible;
        for (int u = 0; u < n; ++u)
            for (int v = u + 1; v < n; ++v) possible.emplace_back(u, v);
        for (int mask = 0; mask < (1 << possible.size()); ++mask) {
            VertexFailureConnectivity solver(n);
            vector<pair<int, int>> edges;
            for (int i = 0; i < (int)possible.size(); ++i) {
                if (!(mask >> i & 1)) continue;
                auto [u, v] = possible[i];
                solver.add_edge(u, v);
                edges.emplace_back(u, v);
            }
            check(solver, n, edges);
        }
    }
    mt19937 rng(20261010);
    for (int tc = 0; tc < 500; ++tc) {
        int n = 1 + rng() % 10;
        VertexFailureConnectivity solver(n);
        vector<pair<int, int>> edges;
        for (int phase = 0; phase < 3; ++phase) {
            for (int i = rng() % 20; i > 0; --i) {
                int u = rng() % n, v = rng() % n;
                solver.add_edge(u, v);
                edges.emplace_back(u, v);
            }
            check(solver, n, edges);
        }
    }
    for (int mode = 0; mode < 4; ++mode) check_large(100000, mode);
    Scanner in;
    Printer out;
    int a, b;
    in.read(a, b);
    out.println(a + b);
}
