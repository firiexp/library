#include "dijkstra_common.cpp"

template <typename T>
struct DijkstraRestoreResult {
    vector<T> dist;
    vector<int> parent;
    vector<int> parent_edge;
};

template <typename T>
DijkstraRestoreResult<T> dijkstra_restore(int s, int n, const vector<edge<T>> &edges) {
    vector<vector<int>> g(n);
    for (int id = 0; id < (int)edges.size(); ++id) g[edges[id].from].push_back(id);
    vector<T> dist(n, INF<T>);
    vector<int> parent(n, -1), parent_edge(n, -1);
    DijkstraPriorityQueue<T> Q;
    dist[s] = 0;
    Q.push(T(0), s);
    while (!Q.empty()) {
        auto [cost, v] = Q.pop();
        if (dist[v] < cost) continue;
        for (int id : g[v]) {
            const auto &e = edges[id];
            T next = cost + e.cost;
            if (dist[e.to] <= next) continue;
            dist[e.to] = next;
            parent[e.to] = v;
            parent_edge[e.to] = id;
            Q.push(next, e.to);
        }
    }
    return {std::move(dist), std::move(parent), std::move(parent_edge)};
}

vector<int> restore_path(int s, int t, const vector<int> &parent) {
    vector<int> path;
    if (t < 0 || t >= (int)parent.size()) return path;
    int v = t;
    while (v != -1) {
        path.push_back(v);
        if (v == s) {
            reverse(path.begin(), path.end());
            return path;
        }
        v = parent[v];
    }
    path.clear();
    return path;
}

template <typename T>
vector<int> restore_edge_path(int s, int t, const DijkstraRestoreResult<T> &result) {
    auto path = restore_path(s, t, result.parent);
    vector<int> edges;
    if (!path.empty()) edges.reserve(path.size() - 1);
    for (int i = 1; i < (int)path.size(); ++i) edges.push_back(result.parent_edge[path[i]]);
    return edges;
}

/**
 * @brief 経路復元付きDijkstra法
 */
