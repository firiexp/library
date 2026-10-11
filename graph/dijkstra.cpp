#ifndef FIRIEXP_LIBRARY_GRAPH_DIJKSTRA_CPP
#define FIRIEXP_LIBRARY_GRAPH_DIJKSTRA_CPP

#include "dijkstra_common.cpp"

template <typename T>
vector<T> dijkstra(int s, const vector<vector<edge<T>>> &G) {
    DijkstraPriorityQueue<T> Q;
    return dijkstra_internal(s, G, Q);
}

#endif

/**
 * @brief Dijkstra法
 */
