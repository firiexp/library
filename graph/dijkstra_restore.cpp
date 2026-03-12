#include "dijkstra_common.cpp"

template <typename T>
struct DijkstraRestoreResult {
    vector<T> dist;
    vector<int> parent;
};

template <typename T>
DijkstraRestoreResult<T> dijkstra_restore(int s, const vector<vector<edge<T>>> &G) {
    vector<int> parent((int)G.size(), -1);
    DijkstraPriorityQueue<T> Q;
    auto dist = dijkstra_internal(s, G, Q, [&](int v, const edge<T> &e) {
        parent[e.to] = v;
    });
    return {dist, parent};
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

/**
 * @brief 経路復元付きDijkstra法
 */
