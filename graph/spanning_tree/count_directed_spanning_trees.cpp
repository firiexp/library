#ifndef FIRIEXP_LIBRARY_GRAPH_SPANNING_TREE_COUNT_DIRECTED_SPANNING_TREES_CPP
#define FIRIEXP_LIBRARY_GRAPH_SPANNING_TREE_COUNT_DIRECTED_SPANNING_TREES_CPP

#include "../../math/linear_algebra/matrix_determinant.cpp"

struct DirectedSpanningTreeEdge {
    int from, to;
    mint weight = 1;
};

mint count_directed_spanning_trees(int n, int root, const vector<DirectedSpanningTreeEdge> &edges) {
    assert(n >= 1 && 0 <= root && root < n);
    vector<vector<mint>> laplacian(n - 1, vector<mint>(n - 1));
    for (auto [from, to, weight] : edges) {
        assert(0 <= from && from < n && 0 <= to && to < n);
        if (from == to || to == root) continue;
        int v = to - (to > root);
        laplacian[v][v] += weight;
        if (from != root) {
            int u = from - (from > root);
            laplacian[v][u] -= weight;
        }
    }
    return matrix_determinant(std::move(laplacian));
}

#endif

/**
 * @brief 有向グラフの全域木数
 */
