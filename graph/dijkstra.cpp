#include "dijkstra_common.cpp"

template <typename T>
vector<T> dijkstra(int s, const vector<vector<edge<T>>> &G) {
    DijkstraPriorityQueue<T> Q;
    return dijkstra_internal(s, G, Q);
}

template <typename T>
vector<T> dijkstra_from_distances(vector<T> initial, const vector<vector<edge<T>>>& G) {
    DijkstraPriorityQueue<T> Q;
    for (int v = 0; v < (int)initial.size(); ++v) {
        if (initial[v] != INF<T>) Q.push(initial[v], v);
    }
    dijkstra_relax(initial, G, Q, [](int, const edge<T>&) {});
    return initial;
}

/**
 * @brief Dijkstra法
 */
