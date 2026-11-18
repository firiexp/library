#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../graph/spanning_tree/kruskal_reconstruction_tree.cpp"

using Edge = KruskalEdge<long long>;

void check(int n, const vector<Edge> &edges) {
    KruskalReconstructionTree<long long> tree(n, edges);
    vector<vector<optional<long long>>> expected(n, vector<optional<long long>>(n));
    set<long long> weights;
    for (const auto &e : edges) weights.insert(e.cost);
    for (long long w : weights) {
        vector<vector<int>> adj(n);
        for (const auto &e : edges) if (e.cost <= w) {
            adj[e.from].push_back(e.to);
            adj[e.to].push_back(e.from);
        }
        for (int u = 0; u < n; ++u) {
            vector<bool> seen(n);
            vector<int> queue{u};
            seen[u] = true;
            for (int i = 0; i < (int)queue.size(); ++i) {
                int v = queue[i];
                if (!expected[u][v]) expected[u][v] = w;
                for (int to : adj[v]) if (!seen[to]) {
                    seen[to] = true;
                    queue.push_back(to);
                }
            }
        }
    }
    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) if (u != v) {
            assert(tree.connection_threshold(u, v) == expected[u][v]);
        }
    }
}

int main() {
    check(0, {});
    check(4, {});
    check(8, {{0, 1, 5}, {2, 3, -1}, {0, 1, LLONG_MIN}, {1, 2, -1}, {3, 4, -1},
              {0, 4, 2}, {1, 1, LLONG_MIN}, {5, 6, LLONG_MAX}});
    mt19937 rng(443);
    for (int trial = 0; trial < 2000; ++trial) {
        int n = 1 + rng() % 12, m = rng() % 30;
        vector<Edge> edges;
        for (int i = 0; i < m; ++i) {
            edges.emplace_back(rng() % n, rng() % n, int(rng() % 7) - 3);
        }
        check(n, edges);
    }

    int n = 200000;
    vector<Edge> edges;
    for (int v = n - 1; v > 0; --v) edges.emplace_back(v, v - 1, v);
    KruskalReconstructionTree<long long> tree(n, std::move(edges));
    for (int v = 1; v < n; ++v) assert(tree.connection_threshold(v, v / 2) == v);
}
