pair<int, vector<int>> tree_center(const vector<vector<int>> &G) {
    int n = G.size();
    if (n == 0) return {0, {}};

    auto bfs = [&](int s, vector<int> &par) {
        vector<int> dist(n, -1);
        queue<int> q;
        dist[s] = 0;
        par.assign(n, -1);
        q.push(s);
        int far = s;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            if (dist[far] < dist[v]) far = v;
            for (auto &&to : G[v]) {
                if (dist[to] != -1) continue;
                dist[to] = dist[v] + 1;
                par[to] = v;
                q.push(to);
            }
        }
        return pair<int, vector<int>>(far, dist);
    };

    vector<int> par;
    int s = bfs(0, par).first;
    auto [t, dist] = bfs(s, par);

    vector<int> path;
    for (int v = t; v != -1; v = par[v]) path.push_back(v);
    reverse(path.begin(), path.end());

    int diam = dist[t];
    vector<int> centers;
    centers.push_back(path[diam / 2]);
    if (diam & 1) centers.push_back(path[diam / 2 + 1]);
    return {(diam + 1) / 2, centers};
}

/**
 * @brief Tree Center
 * @docs _md/tree_center.md
 */
