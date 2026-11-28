struct CycleDetectionDirectedResult {
    vector<int> vertices;
    vector<int> edge_ids;
};

namespace cycle_detection_directed_detail {
int destination(int to) { return to; }
int destination(pair<int, int> edge) { return edge.first; }

template <class Edge, class Emit>
void find_cycle(const vector<vector<Edge>> &g, Emit emit) {
    vector<char> state(g.size());
    vector<size_t> next(g.size());
    vector<int> path;
    for (int root = 0; root < (int)g.size(); ++root) {
        if (state[root]) continue;
        path.push_back(root);
        state[root] = 1;
        while (!path.empty()) {
            int v = path.back();
            if (next[v] == g[v].size()) {
                state[v] = 2;
                path.pop_back();
                continue;
            }
            int to = destination(g[v][next[v]++]);
            if (state[to] == 0) {
                state[to] = 1;
                path.push_back(to);
            } else if (state[to] == 1) {
                for (auto it = find(path.begin(), path.end(), to); it != path.end(); ++it) {
                    int u = *it;
                    emit(u, g[u][next[u] - 1]);
                }
                return;
            }
        }
    }
}
}

vector<int> cycle_detection_directed_vertices(const vector<vector<int>> &g) {
    vector<int> vertices;
    cycle_detection_directed_detail::find_cycle(g, [&](int v, int) { vertices.push_back(v); });
    return vertices;
}

CycleDetectionDirectedResult cycle_detection_directed_with_edges(const vector<vector<pair<int, int>>> &g) {
    CycleDetectionDirectedResult cycle;
    cycle_detection_directed_detail::find_cycle(g, [&](int v, pair<int, int> edge) {
        cycle.vertices.push_back(v);
        cycle.edge_ids.push_back(edge.second);
    });
    return cycle;
}

vector<int> cycle_detection_directed(const vector<vector<pair<int, int>>> &g) {
    vector<int> edge_ids;
    cycle_detection_directed_detail::find_cycle(g, [&](int, pair<int, int> edge) { edge_ids.push_back(edge.second); });
    return edge_ids;
}

/**
 * @brief 有向閉路検出(Directed Cycle Detection)
 */
