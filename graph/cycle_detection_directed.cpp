vector<int> cycle_detection_directed(const vector<vector<pair<int, int>>> &g) {
    int n = g.size();
    vector<int> state(n), st_v, st_e;
    vector<int> cycle;
    auto dfs = [&](auto &&self, int v) -> bool {
        state[v] = 1;
        st_v.emplace_back(v);
        for (auto &&[to, id] : g[v]) {
            st_e.emplace_back(id);
            if (state[to] == 0) {
                if (self(self, to)) return true;
            } else if (state[to] == 1) {
                cycle.emplace_back(id);
                for (int i = (int)st_v.size() - 1; st_v[i] != to; --i) {
                    cycle.emplace_back(st_e[i - 1]);
                }
                reverse(cycle.begin(), cycle.end());
                return true;
            }
            st_e.pop_back();
        }
        st_v.pop_back();
        state[v] = 2;
        return false;
    };
    for (int i = 0; i < n; ++i) {
        if (state[i] == 0 && dfs(dfs, i)) return cycle;
    }
    return {};
}

/**
 * @brief 有向閉路検出(Cycle Detection)
 * @docs _md/cycle_detection_directed.md
 */
