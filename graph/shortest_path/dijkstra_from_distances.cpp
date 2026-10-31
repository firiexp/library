#ifndef FIRIEXP_LIBRARY_GRAPH_DIJKSTRA_FROM_DISTANCES_CPP
#define FIRIEXP_LIBRARY_GRAPH_DIJKSTRA_FROM_DISTANCES_CPP

#include "dijkstra.cpp"

template <typename T>
vector<T> dijkstra_from_distances(vector<T> initial, const vector<vector<edge<T>>>& G) {
    DijkstraPriorityQueue<T> Q;
    for (int v = 0; v < (int)initial.size(); ++v) {
        if (initial[v] != INF<T>) Q.push(initial[v], v);
    }
    dijkstra_relax(initial, G, Q, [](int, const edge<T>&) {});
    return initial;
}

#endif

/**
 * @brief 多始点Dijkstra法
 */
