vector<int> topological_sort(const vector<vector<int>> &g) {
    int n = g.size();
    vector<int> state(n), ord;
    ord.reserve(n);
    auto dfs = [&](auto &&self, int v) -> bool {
        state[v] = 1;
        for (auto &&to : g[v]) {
            if (state[to] == 1) return false;
            if (state[to] == 0 && !self(self, to)) return false;
        }
        state[v] = 2;
        ord.emplace_back(v);
        return true;
    };
    for (int i = 0; i < n; ++i) {
        if (state[i] == 0 && !dfs(dfs, i)) return {};
    }
    reverse(ord.begin(), ord.end());
    return ord;
}

/**
 * @brief Topological sort
 * @docs _md/topological_sort.md
 */
