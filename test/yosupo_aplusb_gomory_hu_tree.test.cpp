#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
template<class T> constexpr T INF = numeric_limits<T>::max() / 2;
#include "../flow/gomory_hu_tree.cpp"

using Tree = GomoryHuTree<long long>;
using Edge = Tree::Edge;

void check(int n, const vector<Edge> &edges) {
    const Tree tree(n, edges);
    assert(int(tree.edges().size()) == n - 1);
    vector<vector<pair<int, long long>>> graph(n);
    for (auto [u, v, capacity] : tree.edges()) {
        assert(0 <= u && u < n && 0 <= v && v < n && u != v && capacity >= 0);
        graph[u].emplace_back(v, capacity);
        graph[v].emplace_back(u, capacity);
    }
    for (int s = 0; s < n; ++s) {
        vector<int> order{s}, parent(n, -1);
        vector<long long> path_min(n, LLONG_MAX);
        parent[s] = s;
        for (int i = 0; i < int(order.size()); ++i) {
            int v = order[i];
            for (auto [u, capacity] : graph[v]) if (u != parent[v]) {
                assert(parent[u] == -1);
                parent[u] = v;
                path_min[u] = min(path_min[v], capacity);
                order.push_back(u);
            }
        }
        assert(int(order.size()) == n);
        for (int t = s + 1; t < n; ++t) {
            long long expected = LLONG_MAX;
            for (int mask = 0; mask < (1 << n); ++mask) {
                if (!(mask >> s & 1) || (mask >> t & 1)) continue;
                long long value = 0;
                for (auto [u, v, capacity] : edges)
                    if (((mask >> u) ^ (mask >> v)) & 1) value += capacity;
                expected = min(expected, value);
            }
            assert(tree.min_cut(s, t) == expected);
            assert(tree.min_cut(t, s) == expected);
            assert(path_min[t] == expected);
        }
    }
    for (auto [s, t, capacity] : tree.edges()) {
        vector<char> seen(n);
        vector<int> order{s};
        seen[s] = true;
        for (int i = 0; i < int(order.size()); ++i) {
            int v = order[i];
            for (auto [u, weight] : graph[v]) {
                if ((v == s && u == t) || seen[u]) continue;
                seen[u] = true;
                order.push_back(u);
            }
        }
        long long value = 0;
        for (auto [u, v, weight] : edges) if (seen[u] != seen[v]) value += weight;
        assert(value == capacity);
    }
}

int main() {
    check(1, {});
    check(1, {{0, 0, LLONG_MAX}});
    check(5, {});
    check(4, {{0, 1, 0}, {1, 1, 7}, {2, 3, 3}, {2, 3, 4}, {3, 2, 5}});
    check(3, {{0, 1, 3}, {1, 2, 4}, {0, 2, 2}});
    check(3, {{0, 1, LLONG_MAX / 2}, {1, 2, LLONG_MAX / 2}, {2, 0, LLONG_MAX / 2}});
    for (int n = 1; n <= 5; ++n) {
        vector<pair<int, int>> pairs;
        for (int u = 0; u < n; ++u) for (int v = u + 1; v < n; ++v) pairs.emplace_back(u, v);
        for (int mask = 0; mask < (1 << pairs.size()); ++mask) {
            vector<Edge> edges;
            for (int i = 0; i < int(pairs.size()); ++i) if (mask >> i & 1)
                edges.push_back({pairs[i].first, pairs[i].second, 1});
            check(n, edges);
        }
    }
    mt19937 rng(348);
    for (int trial = 0; trial < 1200; ++trial) {
        int n = 1 + rng() % 8;
        vector<Edge> edges;
        for (int m = rng() % 25; m > 0; --m)
            edges.push_back({int(rng() % n), int(rng() % n), (long long)(rng() % 10)});
        check(n, edges);
        vector<int> permutation(n);
        iota(permutation.begin(), permutation.end(), 0);
        shuffle(permutation.begin(), permutation.end(), rng);
        for (auto &e : edges) e.u = permutation[e.u], e.v = permutation[e.v];
        shuffle(edges.begin(), edges.end(), rng);
        check(n, edges);
    }
    GomoryHuTree<int> narrow(3, {{0, 1, 100}, {1, 2, 70}});
    assert(narrow.min_cut(0, 2) == 70);
}
