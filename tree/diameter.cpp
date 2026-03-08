pair<int, pair<int, int>> tree_diameter(const vector<vector<int>> &G) {
    int n = G.size();
    if (n == 0) return {0, {-1, -1}};

    vector<int> dist(n);
    int far = 0;
    auto dfs = [&](int v, int p, auto &&f) -> void {
        for (auto &&to : G[v]) {
            if (to == p) continue;
            dist[to] = dist[v] + 1;
            if (dist[far] < dist[to]) far = to;
            f(to, v, f);
        }
    };

    dist[0] = 0;
    dfs(0, -1, dfs);
    int s = far;
    dist[s] = 0;
    dfs(s, -1, dfs);
    return {dist[far], {s, far}};
}

int diameter(const vector<vector<int>> &G) {
    return tree_diameter(G).first;
}

/**
 * @brief 木の直径(Tree Diameter)
 * @docs _md/diameter.md
 */
