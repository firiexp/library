#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../graph/connectivity/edge_failure_connectivity.cpp"
#include "../graph/connectivity/edge_failure_connectivity.cpp"
#include "../graph/connectivity/bridge_tree.cpp"

void check(int n, const vector<pair<int, int>> &edges) {
    EdgeFailureConnectivity graph(n);
    for (int id = 0; id < (int)edges.size(); ++id) {
        auto [u, v] = edges[id];
        int actual = graph.add_edge(u, v);
        assert(actual == id);
    }
    for (int rebuild = 0; rebuild < 2; ++rebuild) {
        graph.build();
        const auto &view = graph;
        for (int removed = 0; removed < (int)edges.size(); ++removed) {
            vector<vector<int>> g(n);
            for (int id = 0; id < (int)edges.size(); ++id) if (id != removed) {
                auto [u, v] = edges[id];
                g[u].push_back(v);
                g[v].push_back(u);
            }
            for (int start = 0; start < n; ++start) {
                vector<char> seen(n);
                queue<int> q;
                seen[start] = true;
                q.push(start);
                while (!q.empty()) {
                    int v = q.front();
                    q.pop();
                    for (int u : g[v]) if (!seen[u]) {
                        seen[u] = true;
                        q.push(u);
                    }
                }
                for (int v = 0; v < n; ++v) {
                    assert(view.connected_without_edge(start, v, removed) == bool(seen[v]));
                }
            }
        }
    }
}

void large(int shape) {
    int n = 200000;
    EdgeFailureConnectivity graph(n);
    for (int v = 1; v < n; ++v) {
        if (shape == 3 && v == n / 2) continue;
        int id = graph.add_edge(shape == 1 ? 0 : v - 1, v);
        assert(id == v - 1 - (shape == 3 && v > n / 2));
    }
    if (shape == 2) graph.add_edge(n - 1, 0);
    graph.build();
    for (int i = 0; i < n - 2; ++i) {
        if (shape == 0) {
            assert(!graph.connected_without_edge(0, n - 1, i));
            assert(graph.connected_without_edge(0, i, i));
        } else if (shape == 1) {
            assert(!graph.connected_without_edge(0, i + 1, i));
            assert(graph.connected_without_edge(0, n - 1, i));
        } else if (shape == 2) {
            assert(graph.connected_without_edge(0, i, i));
        } else {
            assert(!graph.connected_without_edge(0, n - 1, i));
            assert(graph.connected_without_edge(0, n / 2 - 1, n - 3));
        }
        assert(graph.connected_without_edge(i, i, i));
    }
    int loop = graph.add_edge(0, 0);
    int parallel = graph.add_edge(0, 1);
    graph.build();
    assert(graph.connected_without_edge(0, 1, 0));
    assert(graph.connected_without_edge(0, 1, parallel));
    assert(graph.connected_without_edge(0, 1, loop));
}

int main() {
    check(0, {});
    check(4, {});
    check(5, {{0, 0}, {0, 1}, {1, 1}, {0, 1}, {1, 2}, {3, 4}, {4, 4}});
    mt19937 rng(298);
    for (int trial = 0; trial < 3000; ++trial) {
        int n = 1 + rng() % 8, m = rng() % 15;
        vector<pair<int, int>> edges(m);
        for (auto &[u, v] : edges) {
            u = rng() % n;
            v = rng() % n;
        }
        check(n, edges);
    }
    EdgeFailureConnectivity rebuilt(3);
    int first = rebuilt.add_edge(0, 1);
    rebuilt.build();
    assert(!rebuilt.connected_without_edge(0, 2, first));
    int second = rebuilt.add_edge(1, 2);
    rebuilt.build();
    assert(first == 0 && second == 1);
    assert(!rebuilt.connected_without_edge(0, 2, first));
    int third = rebuilt.add_edge(2, 0);
    rebuilt.build();
    for (int id : {first, second, third}) assert(rebuilt.connected_without_edge(0, 2, id));
    for (int shape = 0; shape < 4; ++shape) large(shape);
}
