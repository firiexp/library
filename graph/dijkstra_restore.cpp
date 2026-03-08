#include "dijkstra.cpp"

template <typename T>
struct DijkstraRestoreResult {
    vector<T> dist;
    vector<int> parent;
};

template <typename T>
DijkstraRestoreResult<T> dijkstra_restore(int s, vector<vector<edge<T>>> &G) {
    int n = (int)G.size();
    vector<T> dist(n, INF<T>);
    vector<int> parent(n, -1);
    priority_queue<pair<T, int>, vector<pair<T, int>>, greater<>> Q;
    dist[s] = 0;
    Q.emplace(0, s);
    while (!Q.empty()) {
        T cost;
        int v;
        tie(cost, v) = Q.top();
        Q.pop();
        if (dist[v] < cost) continue;
        for (auto &&e : G[v]) {
            T nxt = cost + e.cost;
            if (dist[e.to] <= nxt) continue;
            dist[e.to] = nxt;
            parent[e.to] = v;
            Q.emplace(nxt, e.to);
        }
    }
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
 * @docs _md/dijkstra_restore.md
 */
