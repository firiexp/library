#ifndef FIRIEXP_LIBRARY_GRAPH_SHORTEST_PATH_FLOYD_WARSHALL_CPP
#define FIRIEXP_LIBRARY_GRAPH_SHORTEST_PATH_FLOYD_WARSHALL_CPP

#include "../edge.cpp"

template <class T>
vector<vector<T>> floyd_warshall(int n, const vector<edge<T>> &edges) {
    static_assert(numeric_limits<T>::is_integer && numeric_limits<T>::is_signed);
    static_assert(0 < INF<T> && INF<T> <= numeric_limits<T>::max() / 2);
    assert(n >= 1);
    vector<vector<T>> dist(n, vector<T>(n, INF<T>));
    for (int v = 0; v < n; ++v) dist[v][v] = 0;
    for (const auto &e : edges) {
        assert(0 <= e.from && e.from < n && 0 <= e.to && e.to < n);
        assert(-INF<T> < e.cost && e.cost < INF<T>);
        dist[e.from][e.to] = min(dist[e.from][e.to], e.cost);
    }
    for (int k = 0; k < n; ++k) {
        if (dist[k][k] < 0) return {};
        for (int u = 0; u < n; ++u) {
            if (dist[u][k] == INF<T>) continue;
            for (int v = 0; v < n; ++v) {
                if (dist[k][v] == INF<T>) continue;
                T next = dist[u][k] + dist[k][v];
                dist[u][v] = min(dist[u][v], next);
            }
        }
    }
    return dist;
}

#endif

/**
 * @brief 全頂点対最短距離(Floyd–Warshall法)
 */
