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

vector<int> topological_sort_lexmin(const vector<vector<int>> &g) {
    int n = g.size();
    vector<int> indegree(n), ord;
    ord.reserve(n);
    for (const auto &edges : g) {
        for (int to : edges) ++indegree[to];
    }
    priority_queue<int, vector<int>, greater<int>> ready;
    for (int v = 0; v < n; ++v) {
        if (indegree[v] == 0) ready.push(v);
    }
    while (!ready.empty()) {
        int v = ready.top();
        ready.pop();
        ord.push_back(v);
        for (int to : g[v]) {
            if (--indegree[to] == 0) ready.push(to);
        }
    }
    if ((int)ord.size() != n) return {};
    return ord;
}

/**
 * @brief トポロジカルソート(Topological Sort)
 */
