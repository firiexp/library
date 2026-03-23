struct CycleDetectionUndirectedResult {
    vector<int> vertices;
    vector<int> edge_ids;
};

CycleDetectionUndirectedResult cycle_detection_undirected(const vector<pair<int, int>> &edges, int n) {
    int m = edges.size();
    vector<vector<pair<int, int>>> g(n);
    for (int i = 0; i < m; ++i) {
        auto [u, v] = edges[i];
        g[u].push_back({v, i});
        g[v].push_back({u, i});
    }

    vector<int> dep(n, -1), par_v(n, -1), par_e(n, -1);
    vector<char> used_e(m, 0);
    auto dfs = [&](auto &&self, int v, int d) -> void {
        dep[v] = d;
        for (auto &&[to, id] : g[v]) {
            if (dep[to] != -1) continue;
            used_e[id] = 1;
            par_v[to] = v;
            par_e[to] = id;
            self(self, to, d + 1);
        }
    };
    for (int i = 0; i < n; ++i) {
        if (dep[i] == -1) dfs(dfs, i, 0);
    }

    for (int id = 0; id < m; ++id) {
        if (used_e[id]) continue;
        auto [a, b] = edges[id];
        if (dep[a] > dep[b]) swap(a, b);
        vector<int> vs = {b}, es;
        while (vs.back() != a) {
            es.emplace_back(par_e[vs.back()]);
            vs.emplace_back(par_v[vs.back()]);
        }
        es.emplace_back(id);
        return {vs, es};
    }
    return {{}, {}};
}

/**
 * @brief 無向閉路検出(Undirected Cycle Detection)
 */
