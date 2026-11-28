#define STANDALONE

#include <bits/stdc++.h>
using namespace std;

#include "../graph/connectivity/st_numbering.cpp"

using Graph = vector<vector<int>>;

void add_edge(Graph &g, int u, int v) {
    g[u].push_back(v);
    g[v].push_back(u);
}

bool connected_without(const Graph &g, int removed) {
    int start = removed == 0 ? 1 : 0;
    vector<int> queue{start};
    vector<bool> seen(g.size());
    seen[start] = true;
    for (size_t i = 0; i < queue.size(); ++i) {
        for (int u : g[queue[i]]) {
            if (u == removed || seen[u]) continue;
            seen[u] = true;
            queue.push_back(u);
        }
    }
    return queue.size() + (removed != -1) == g.size();
}

bool exists(Graph g, int s, int t) {
    if (!connected_without(g, -1)) return false;
    add_edge(g, s, t);
    for (int v = 0; v < int(g.size()); ++v) {
        if (!connected_without(g, v)) return false;
    }
    return true;
}

void check(const Graph &g, int s, int t, bool expected) {
    auto order = st_numbering(g, s, t);
    assert(expected == !order.empty());
    if (order.empty()) return;
    int n = g.size();
    assert(int(order.size()) == n && order.front() == s && order.back() == t);
    vector<int> rank(n, -1);
    for (int i = 0; i < n; ++i) {
        int v = order[i];
        assert(0 <= v && v < n && rank[v] == -1);
        rank[v] = i;
    }
    for (int v = 0; v < n; ++v) {
        bool earlier = v == s, later = v == t;
        for (int u : g[v]) {
            earlier |= rank[u] < rank[v];
            later |= rank[u] > rank[v];
        }
        assert(earlier && later);
    }
}

int main() {
    for (int n = 2; n <= 5; ++n) {
        int pairs = n * (n - 1) / 2;
        for (int mask = 0; mask < (1 << pairs); ++mask) {
            Graph g(n);
            int bit = 0;
            for (int u = 0; u < n; ++u) {
                for (int v = u + 1; v < n; ++v, ++bit) {
                    if ((mask >> bit) & 1) add_edge(g, u, v);
                }
            }
            for (int s = 0; s < n; ++s) {
                for (int t = 0; t < n; ++t) {
                    if (s != t) check(g, s, t, exists(g, s, t));
                }
            }
        }
    }

    Graph multi(3);
    add_edge(multi, 1, 1);
    add_edge(multi, 1, 0);
    add_edge(multi, 0, 1);
    add_edge(multi, 1, 2);
    check(multi, 2, 0, true);
    check(multi, 2, 1, false);
    check(multi, 1, 1, false);
    check(multi, -1, 0, false);
    check(multi, 1, 3, false);

    int n = 200000;
    Graph path(n);
    for (int v = 1; v < n; ++v) add_edge(path, v - 1, v);
    check(path, n - 1, 0, true);
    path.emplace_back();
    add_edge(path, n / 2, n);
    check(path, n - 1, 0, false);
}
