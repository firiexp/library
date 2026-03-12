vector<int> cycle_detection_directed(const vector<vector<pair<int, int>>> &g) {
    int n = g.size();
    vector<int> state(n), pos(n, -1), parent_edge(n, -1), path_v;
    for (int s = 0; s < n; ++s) {
        if (state[s] != 0) continue;
        vector<pair<int, int>> st = {{s, 0}};
        state[s] = 1;
        pos[s] = 0;
        path_v.emplace_back(s);
        while (!st.empty()) {
            int v = st.back().first;
            int &it = st.back().second;
            if (it == (int)g[v].size()) {
                state[v] = 2;
                pos[v] = -1;
                path_v.pop_back();
                st.pop_back();
                continue;
            }
            auto [to, id] = g[v][it++];
            if (state[to] == 0) {
                parent_edge[to] = id;
                state[to] = 1;
                pos[to] = path_v.size();
                path_v.emplace_back(to);
                st.emplace_back(to, 0);
                continue;
            }
            if (state[to] == 1) {
                vector<int> cycle;
                for (int i = pos[to] + 1; i < (int)path_v.size(); ++i) {
                    cycle.emplace_back(parent_edge[path_v[i]]);
                }
                cycle.emplace_back(id);
                return cycle;
            }
        }
    }
    return {};
}

/**
 * @brief 有向閉路検出(Cycle Detection)
 */
