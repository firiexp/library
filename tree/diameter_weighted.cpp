template<class T>
pair<T, pair<int, int>> tree_diameter_weighted(const vector<vector<pair<int, T>>> &G) {
    int n = G.size();
    if (n == 0) return {T(), {-1, -1}};

    vector<T> dist(n);
    int far = 0;
    auto dfs = [&](int v, int p, auto &&f) -> void {
        for (auto &&e : G[v]) {
            int to = e.first;
            T cost = e.second;
            if (to == p) continue;
            dist[to] = dist[v] + cost;
            if (dist[far] < dist[to]) far = to;
            f(to, v, f);
        }
    };

    dist[0] = T();
    dfs(0, -1, dfs);
    int s = far;
    dist[s] = T();
    dfs(s, -1, dfs);
    return {dist[far], {s, far}};
}

/**
 * @brief Tree Diameter (Weighted)
 * @docs _md/diameter_weighted.md
 */
