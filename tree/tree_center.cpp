pair<int, vector<int>> tree_center(const vector<vector<int>> &G) {
    int n = G.size();
    if (n == 0) return {0, {}};

    vector<int> dist(n), par(n), q(n);
    auto bfs = [&](int s, bool record_parent) {
        fill(dist.begin(), dist.end(), -1);
        dist[s] = 0;
        if (record_parent) par[s] = -1;
        int head = 0, tail = 0;
        q[tail++] = s;
        int far = s;
        while (head < tail) {
            int v = q[head++];
            if (dist[far] < dist[v]) far = v;
            for (auto &&to : G[v]) {
                if (dist[to] != -1) continue;
                dist[to] = dist[v] + 1;
                if (record_parent) par[to] = v;
                q[tail++] = to;
            }
        }
        return far;
    };

    int s = bfs(0, false);
    int t = bfs(s, true);

    int diam = dist[t];
    int v = t;
    for (int i = 0; i < diam / 2; ++i) v = par[v];
    if (diam & 1) return {(diam + 1) / 2, vector<int>{par[v], v}};
    return {diam / 2, vector<int>{v}};
}

/**
 * @brief 木の中心(Tree Center)
 */
