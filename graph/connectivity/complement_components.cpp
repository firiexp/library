vector<vector<int>> complement_components(const vector<vector<int>> &g) {
    int n = g.size();
    vector<int> next(n + 1), marked(n, -1);
    for(int v = 0; v < n; ++v) next[v] = v + 1;
    next[n] = 0;
    vector<vector<int>> components;
    while(next[n] != n) {
        int start = next[n];
        next[n] = next[start];
        components.push_back({start});
        auto &component = components.back();
        for(size_t i = 0; i < component.size(); ++i) {
            int v = component[i];
            for(int u : g[v]) marked[u] = v;
            int prev = n;
            while(next[prev] != n) {
                int u = next[prev];
                if(marked[u] == v) {
                    prev = u;
                } else {
                    next[prev] = next[u];
                    component.push_back(u);
                }
            }
        }
    }
    return components;
}

/**
 * @brief 補グラフの連結成分
 */
