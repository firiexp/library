#ifndef FIRIEXP_LIBRARY_GRAPH_K_SHORTEST_WALK_CPP
#define FIRIEXP_LIBRARY_GRAPH_K_SHORTEST_WALK_CPP

#include "edge.cpp"

template <class T>
vector<T> k_shortest_walk(int s, int t, int k, const vector<vector<edge<T>>> &g) {
    int n = (int)g.size();
    assert(0 <= s && s < n && 0 <= t && t < n && k >= 0);
    if (k == 0) return {};
    vector<size_t> reverse_start(n + 1);
    for (int v = 0; v < n; ++v) {
        for (const auto &e : g[v]) {
            assert(0 <= e.to && e.to < n && e.cost >= 0);
            ++reverse_start[e.to + 1];
        }
    }
    for (int v = 0; v < n; ++v) reverse_start[v + 1] += reverse_start[v];
    size_t m = reverse_start[n];
    vector<pair<int, int>> reverse_edges(m);
    auto cursor = reverse_start;
    for (int v = 0; v < n; ++v) {
        for (int i = 0; i < (int)g[v].size(); ++i) {
            reverse_edges[cursor[g[v][i].to]++] = {v, i};
        }
    }
    vector<T> dist(n);
    vector<char> reached(n);
    vector<int> parent_edge(n, -1), order;
    priority_queue<pair<T, int>, vector<pair<T, int>>, greater<>> queue;
    reached[t] = true;
    queue.emplace(T(0), t);
    while (!queue.empty()) {
        auto [value, v] = queue.top();
        queue.pop();
        if (value != dist[v]) continue;
        order.push_back(v);
        for (size_t ei = reverse_start[v]; ei < reverse_start[v + 1]; ++ei) {
            auto [u, i] = reverse_edges[ei];
            T next = value + g[u][i].cost;
            if (reached[u] && dist[u] <= next) continue;
            reached[u] = true;
            dist[u] = next;
            parent_edge[u] = i;
            queue.emplace(next, u);
        }
    }
    if (!reached[s]) return {};
    vector<T> result{dist[s]};
    if (k == 1) return result;

    struct Node { T delta; int to, left, right, rank; };
    vector<Node> nodes{ { T(0), -1, 0, 0, 0 } };
    nodes.reserve(m + 1);
    auto meld = [&](auto &&self, int a, int b, bool persistent) -> int {
        if (!a) return b;
        if (!b) return a;
        if (nodes[b].delta < nodes[a].delta) swap(a, b);
        if (persistent) {
            Node copy = nodes[a];
            a = (int)nodes.size();
            nodes.push_back(copy);
        }
        int right = self(self, nodes[a].right, b, persistent);
        nodes[a].right = right;
        if (nodes[nodes[a].left].rank < nodes[right].rank) swap(nodes[a].left, nodes[a].right);
        nodes[a].rank = nodes[nodes[a].right].rank + 1;
        return a;
    };
    vector<int> roots(n);
    for (int v : order) {
        int heap = 0;
        for (int i = 0; i < (int)g[v].size(); ++i) {
            const auto &e = g[v][i];
            if (i == parent_edge[v] || !reached[e.to]) continue;
            int id = (int)nodes.size();
            nodes.push_back({e.cost + dist[e.to] - dist[v], e.to, 0, 0, 1});
            heap = meld(meld, heap, id, false);
        }
        if (parent_edge[v] != -1) {
            int parent = g[v][parent_edge[v]].to;
            heap = meld(meld, heap, roots[parent], true);
        }
        roots[v] = heap;
    }
    if (roots[s]) queue.emplace(dist[s] + nodes[roots[s]].delta, roots[s]);
    while (!queue.empty() && (int)result.size() < k) {
        auto [value, id] = queue.top();
        queue.pop();
        result.push_back(value);
        if ((int)result.size() == k) break;
        const auto &node = nodes[id];
        for (int child : {node.left, node.right}) {
            if (child) queue.emplace(value - node.delta + nodes[child].delta, child);
        }
        int next = roots[node.to];
        if (next) queue.emplace(value + nodes[next].delta, next);
    }
    return result;
}

#endif

/**
 * @brief K番目の最短ウォーク
 */
