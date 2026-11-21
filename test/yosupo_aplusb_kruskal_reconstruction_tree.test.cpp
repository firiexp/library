#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
template<class T> constexpr T INF = numeric_limits<T>::max() / 32 * 15 + 208;
#include "../graph/spanning_tree/kruskal_reconstruction_tree.cpp"

using Edge = KruskalEdge<long long>;

void check(int n, const vector<Edge> &edges) {
    const KruskalReconstructionTree<long long> tree(n, edges);
    assert((int)tree.leaf_order.size() == n && (int)tree.leaf_pos.size() == n);
    for (int i = 0; i < n; ++i) {
        int v = tree.leaf_order[i];
        assert(0 <= v && v < n && tree.leaf_pos[v] == i);
    }
    vector<vector<optional<long long>>> expected(n, vector<optional<long long>>(n));
    set<long long> weights{LLONG_MIN, LLONG_MAX};
    for (const auto &e : edges) {
        weights.insert(e.cost);
        if (e.cost != LLONG_MIN) weights.insert(e.cost - 1);
    }
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
            auto [l, r] = tree.component_range(u, w);
            assert(0 <= l && l < r && r <= n);
            assert(r - l == (int)queue.size() && tree.component_size(u, w) == r - l);
            for (int i = l; i < r; ++i) assert(seen[tree.leaf_order[i]]);
        }
    }
    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) if (u != v) {
            long long weight = tree.connection_threshold(u, v);
            assert(weight == expected[u][v].value_or(INF<long long>));
        }
    }
}

int main() {
    check(0, {});
    check(1, {});
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
    for (int v = 1; v < n; ++v) {
        assert(tree.connection_threshold(v, v / 2) == v);
        assert(tree.component_size(0, v) == v + 1);
        assert(tree.component_size(v, v - 1) == 1);
    }
}
