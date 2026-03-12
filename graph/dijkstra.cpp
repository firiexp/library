#include "dijkstra_common.cpp"

template <typename T>
vector<T> dijkstra(int s, const vector<vector<edge<T>>> &G) {
    DijkstraPriorityQueue<T> Q;
    return dijkstra_internal(s, G, Q);
}

/**
 * @brief Dijkstra法
 */
