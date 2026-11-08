#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
constexpr int MOD = 998244353;
#include "../graph/spanning_tree/count_directed_spanning_trees.cpp"
#include "../graph/spanning_tree/count_directed_spanning_trees.cpp"
#include "../graph/spanning_tree/count_spanning_trees.cpp"

mint brute(int n, int root, const vector<DirectedSpanningTreeEdge> &edges) {
    mint answer = 0;
    for (int mask = 0; mask < (1 << edges.size()); ++mask) {
        if (__builtin_popcount(unsigned(mask)) != n - 1) continue;
        vector<vector<int>> graph(n);
        mint weight = 1;
        for (int i = 0; i < int(edges.size()); ++i) if (mask >> i & 1) {
            auto [u, v, w] = edges[i];
            graph[u].push_back(v);
            weight *= w;
        }
        vector<bool> seen(n);
        vector<int> queue{root};
        seen[root] = true;
        for (int i = 0; i < int(queue.size()); ++i) {
            for (int v : graph[queue[i]]) if (!seen[v]) {
                seen[v] = true;
                queue.push_back(v);
            }
        }
        if (int(queue.size()) == n) answer += weight;
    }
    return answer;
}

void check(int n, const vector<DirectedSpanningTreeEdge> &edges) {
    auto copy = edges;
    for (int root = 0; root < n; ++root) {
        auto answer = count_directed_spanning_trees(n, root, edges);
        assert(answer == brute(n, root, edges));
    }
    assert(edges.size() == copy.size());
    for (int i = 0; i < int(edges.size()); ++i) {
        assert(edges[i].from == copy[i].from && edges[i].to == copy[i].to);
        assert(edges[i].weight == copy[i].weight);
    }
}

int main() {
    check(1, {});
    check(1, {{0, 0, 0}, {0, 0, -2}});
    check(3, {});
    check(3, {{0, 1}, {1, 0}});
    check(2, {{0, 1, 3}, {0, 1, -3}, {1, 0, 7}});
    check(3, {{0, 1, 2}, {0, 2, 3}, {1, 2, 5}, {2, 2, 8}});
    check(3, {{0, 1, 0}, {1, 2, 3}, {2, 0, -4}});
    vector<DirectedSpanningTreeEdge> star{{0, 1, 2}, {0, 2, 3}, {0, 3, 5}};
    assert(count_directed_spanning_trees(4, 0, star) == mint(30));
    check(4, star);
    for (auto &edge : star) swap(edge.from, edge.to);
    assert(count_directed_spanning_trees(4, 0, star) == mint(0));
    check(4, star);
    for (int n = 1; n <= 3; ++n) {
        for (int mask = 0; mask < (1 << (n * n)); ++mask) {
            vector<DirectedSpanningTreeEdge> edges;
            for (int u = 0; u < n; ++u) for (int v = 0; v < n; ++v) {
                if (mask >> (u * n + v) & 1) edges.push_back({u, v});
            }
            check(n, edges);
        }
    }
    mt19937 rng(417);
    for (int trial = 0; trial < 1500; ++trial) {
        int n = 1 + rng() % 7, m = rng() % 13;
        vector<DirectedSpanningTreeEdge> edges;
        for (int i = 0; i < m; ++i)
            edges.push_back({int(rng() % n), int(rng() % n), int(rng() % 7) - 3});
        check(n, edges);
        for (auto &edge : edges) edge.weight = 1;
        check(n, edges);
    }
    for (int n = 2; n <= 25; ++n) {
        vector<DirectedSpanningTreeEdge> edges;
        for (int u = 0; u < n; ++u) for (int v = 0; v < n; ++v) edges.push_back({u, v});
        for (int root = 0; root < n; ++root)
            assert(count_directed_spanning_trees(n, root, edges) == mint(n).pow(n - 2));
    }
}
