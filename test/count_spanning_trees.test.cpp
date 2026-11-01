#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
constexpr int MOD = 998244353;
#include "../graph/spanning_tree/count_spanning_trees.cpp"

mint brute(int n, const vector<SpanningTreeEdge> &edges) {
    mint answer = 0;
    for (int mask = 0; mask < (1 << edges.size()); ++mask) {
        if (__builtin_popcount(unsigned(mask)) != n - 1) continue;
        vector<vector<int>> graph(n);
        mint weight = 1;
        for (int i = 0; i < int(edges.size()); ++i) if (mask >> i & 1) {
            auto [u, v, w] = edges[i];
            graph[u].push_back(v);
            graph[v].push_back(u);
            weight *= w;
        }
        vector<bool> seen(n);
        vector<int> queue{0};
        seen[0] = true;
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

int main() {
    assert(count_spanning_trees(1, {}) == mint(1));
    assert(count_spanning_trees(1, {{0, 0, 0}, {0, 0, -2}}) == mint(1));
    assert(count_spanning_trees(2, {}) == mint(0));
    assert(count_spanning_trees(2, {{0, 1, 3}, {1, 0, -3}}) == mint(0));
    assert(count_spanning_trees(3, {{0, 1}, {1, 2}, {2, 0}}) == mint(3));
    assert(count_spanning_trees(3, {{0, 1, 2}, {1, 2}, {2, 0}}) == mint(5));
    mt19937 rng(299);
    for (int trial = 0; trial < 3000; ++trial) {
        int n = 1 + rng() % 7, m = rng() % 13;
        vector<SpanningTreeEdge> edges;
        for (int i = 0; i < m; ++i)
            edges.push_back({int(rng() % n), int(rng() % n), int(rng() % 7) - 3});
        assert(count_spanning_trees(n, edges) == brute(n, edges));
        for (auto &edge : edges) edge.weight = 1;
        assert(count_spanning_trees(n, edges) == brute(n, edges));
    }
    for (int n = 2; n <= 25; ++n) {
        vector<SpanningTreeEdge> edges;
        for (int u = 0; u < n; ++u)
            for (int v = u + 1; v < n; ++v) edges.push_back({u, v});
        assert(count_spanning_trees(n, edges) == mint(n).pow(n - 2));
    }
}
