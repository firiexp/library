#ifndef FIRIEXP_LIBRARY_GRAPH_SPANNING_TREE_COUNT_SPANNING_TREES_CPP
#define FIRIEXP_LIBRARY_GRAPH_SPANNING_TREE_COUNT_SPANNING_TREES_CPP

#include "../../math/linear_algebra/matrix_determinant.cpp"

struct SpanningTreeEdge {
    int u, v;
    mint weight = 1;
};

mint count_spanning_trees(int n, const vector<SpanningTreeEdge> &edges) {
    assert(n >= 1);
    vector<vector<mint>> laplacian(n - 1, vector<mint>(n - 1));
    for (auto [u, v, weight] : edges) {
        assert(0 <= u && u < n && 0 <= v && v < n);
        if (u == v) continue;
        if (u < n - 1) laplacian[u][u] += weight;
        if (v < n - 1) laplacian[v][v] += weight;
        if (u < n - 1 && v < n - 1) {
            laplacian[u][v] -= weight;
            laplacian[v][u] -= weight;
        }
    }
    return matrix_determinant(std::move(laplacian));
}

#endif

/**
 * @brief 無向グラフの全域木数
 */
