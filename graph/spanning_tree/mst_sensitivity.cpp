#ifndef FIRIEXP_LIBRARY_GRAPH_MST_SENSITIVITY_CPP
#define FIRIEXP_LIBRARY_GRAPH_MST_SENSITIVITY_CPP

#include "kruskal.cpp"

struct MSTSensitivityResult {
    bool exists;
    long long cost;
    vector<optional<long long>> forced, forbidden;
};

MSTSensitivityResult mst_sensitivity(int n, const vector<KruskalEdge<long long>> &edges) {
    assert(n >= 1);
    int m = (int)edges.size();
    KruskalResult<long long> mst{false, 0, {}};
    mst.edge_id.reserve(n - 1);
    vector<int> non_tree;
    non_tree.reserve(max(0, m - n + 1));
    {
        auto indexed = edges;
        for (int i = 0; i < m; ++i) indexed[i].idx = i;
        sort(indexed.begin(), indexed.end(), [](const auto &a, const auto &b) {
            if (a.cost != b.cost) return a.cost < b.cost;
            return a.idx < b.idx;
        });
        KruskalUnionFind uf(n);
        for (const auto &e : indexed) {
            if (uf.unite(e.from, e.to)) {
                mst.cost += e.cost;
                mst.edge_id.push_back(e.idx);
            } else if (e.from != e.to) {
                non_tree.push_back(e.idx);
            }
        }
    }
    mst.exists = (int)mst.edge_id.size() == n - 1;
    if (!mst.exists) mst.cost = 0;
    MSTSensitivityResult result{mst.exists, mst.cost,
                                vector<optional<long long>>(m), vector<optional<long long>>(m)};
    if (!mst.exists) return result;
    vector<char> in_tree(m);
    vector<vector<pair<int, int>>> tree(n);
    for (int id : mst.edge_id) {
        in_tree[id] = 1;
        result.forced[id] = mst.cost;
        const auto &e = edges[id];
        tree[e.from].emplace_back(e.to, id);
        tree[e.to].emplace_back(e.from, id);
    }
    int height = 1;
    while ((1LL << height) <= n) ++height;
    vector<vector<int>> parent(height, vector<int>(n));
    vector<vector<long long>> maximum(height, vector<long long>(n, LLONG_MIN));
    vector<int> depth(n), parent_edge(n, -1), order{0};
    for (int i = 0; i < (int)order.size(); ++i) {
        int v = order[i];
        for (auto [u, id] : tree[v]) {
            if (u == parent[0][v]) continue;
            parent[0][u] = v;
            parent_edge[u] = id;
            maximum[0][u] = edges[id].cost;
            depth[u] = depth[v] + 1;
            order.push_back(u);
        }
    }
    for (int k = 1; k < height; ++k) {
        for (int v = 0; v < n; ++v) {
            int u = parent[k - 1][v];
            parent[k][v] = parent[k - 1][u];
            maximum[k][v] = max(maximum[k - 1][v], maximum[k - 1][u]);
        }
    }
    auto path = [&](int u, int v) {
        long long weight = LLONG_MIN;
        if (depth[u] < depth[v]) swap(u, v);
        int difference = depth[u] - depth[v];
        for (int k = 0; k < height; ++k) {
            if ((difference >> k) & 1) {
                weight = max(weight, maximum[k][u]);
                u = parent[k][u];
            }
        }
        if (u == v) return make_pair(u, weight);
        for (int k = height - 1; k >= 0; --k) {
            if (parent[k][u] == parent[k][v]) continue;
            weight = max({weight, maximum[k][u], maximum[k][v]});
            u = parent[k][u];
            v = parent[k][v];
        }
        return make_pair(parent[0][u], max({weight, maximum[0][u], maximum[0][v]}));
    };
    for (int i = 0; i < m; ++i) {
        if (in_tree[i]) continue;
        result.forbidden[i] = mst.cost;
    }
    KruskalUnionFind skip(n);
    vector<int> top(n);
    iota(top.begin(), top.end(), 0);
    auto replace = [&](int v, int ancestor, long long weight) {
        int representative = skip.root(v), x = top[representative];
        while (depth[x] > depth[ancestor]) {
            int id = parent_edge[x];
            result.forbidden[id] = mst.cost + weight - edges[id].cost;
            int highest = top[skip.root(parent[0][x])];
            skip.unite(representative, parent[0][x]);
            representative = skip.root(representative);
            top[representative] = highest;
            x = highest;
        }
    };
    for (int id : non_tree) {
        const auto &e = edges[id];
        auto [ancestor, weight] = path(e.from, e.to);
        result.forced[id] = mst.cost + e.cost - weight;
        replace(e.from, ancestor, e.cost);
        replace(e.to, ancestor, e.cost);
    }
    return result;
}

#endif

/**
 * @brief 最小全域木の辺別制約コスト
 */
