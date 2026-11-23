struct CycleDetectionUndirectedResult {
    vector<int> vertices;
    vector<int> edge_ids;
};

CycleDetectionUndirectedResult cycle_detection_undirected(const vector<pair<int, int>> &edges, int n) {
    if (edges.empty()) return {};
    vector<size_t> offset((size_t)n + 1);
    for (auto [u, v] : edges) {
        ++offset[u];
        ++offset[v];
    }
    for (size_t v = 1; v < offset.size(); ++v) offset[v] += offset[v - 1];
    vector<pair<int, int>> adj(offset[n]);
    for (int id = (int)(edges.size() - 1); id >= 0; --id) {
        auto [u, v] = edges[id];
        adj[--offset[u]] = {v, id};
        adj[--offset[v]] = {u, id};
    }

    struct Frame {
        int vertex, parent_edge;
        size_t next;
    };
    vector<Frame> path;
    path.reserve(n);
    vector<char> visited(n);
    for (int root = 0; root < n; ++root) {
        if (visited[root]) continue;
        visited[root] = true;
        path.push_back({root, -1, offset[root]});
        while (!path.empty()) {
            auto &frame = path.back();
            if (frame.next == offset[frame.vertex + 1]) {
                path.pop_back();
                continue;
            }
            auto [to, id] = adj[frame.next++];
            if (id == frame.parent_edge) continue;
            if (!visited[to]) {
                visited[to] = true;
                path.push_back({to, id, offset[to]});
                continue;
            }
            CycleDetectionUndirectedResult cycle;
            while (path.back().vertex != to) {
                cycle.vertices.push_back(path.back().vertex);
                cycle.edge_ids.push_back(path.back().parent_edge);
                path.pop_back();
            }
            cycle.vertices.push_back(to);
            cycle.edge_ids.push_back(id);
            return cycle;
        }
    }
    return {};
}

/**
 * @brief 無向閉路検出(Undirected Cycle Detection)
 */
