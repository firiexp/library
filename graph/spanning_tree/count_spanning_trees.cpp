#ifndef FIRIEXP_LIBRARY_GRAPH_SPANNING_TREE_COUNT_SPANNING_TREES_CPP
#define FIRIEXP_LIBRARY_GRAPH_SPANNING_TREE_COUNT_SPANNING_TREES_CPP

#include "../../math/linear_algebra/matrix_determinant.cpp"

struct SpanningTreeEdge {
    int u, v;
    mint weight = 1;
};

mint count_spanning_trees(int n, const vector<SpanningTreeEdge> &edges) {
    assert(n >= 1);
    vector<int> degree(n);
    for (auto [u, v, weight] : edges) {
        assert(0 <= u && u < n && 0 <= v && v < n);
        if (u == v) continue;
        ++degree[u];
        ++degree[v];
    }
    mint factor = 1;
    int k = n;
    vector<int> index;
    if (n > 1 && find(degree.begin(), degree.end(), 0) != degree.end()) return 0;
    if (find(degree.begin(), degree.end(), 1) != degree.end()) {
        vector<int> start(n + 1);
        for (int v = 0; v < n; ++v) start[v + 1] = start[v] + degree[v];
        vector<int> adjacent(start[n]), cursor = start;
        for (int id = 0; id < int(edges.size()); ++id) {
            auto [u, v, weight] = edges[id];
            if (u == v) continue;
            adjacent[cursor[u]++] = id;
            adjacent[cursor[v]++] = id;
        }
        vector<char> seen(n);
        vector<int> Q;
        Q.reserve(n);
        Q.push_back(0);
        seen[0] = true;
        for (int i = 0; i < int(Q.size()); ++i) {
            int v = Q[i];
            for (int j = start[v]; j < start[v + 1]; ++j) {
                const auto &e = edges[adjacent[j]];
                int u = e.u ^ e.v ^ v;
                if (!seen[u]) {
                    seen[u] = true;
                    Q.push_back(u);
                }
            }
        }
        if (int(Q.size()) != n) return 0;
        Q.clear();
        for (int v = 0; v < n; ++v) if (degree[v] == 1) Q.push_back(v);
        for (int i = 0; i < int(Q.size()); ++i) {
            int v = Q[i];
            if (degree[v] != 1) continue;
            for (int j = start[v]; j < start[v + 1]; ++j) {
                const auto &e = edges[adjacent[j]];
                int u = e.u ^ e.v ^ v;
                if (degree[u] == 0) continue;
                factor *= e.weight;
                degree[v] = 0;
                if (--degree[u] == 1) Q.push_back(u);
                break;
            }
        }
        k = 0;
        index.assign(n, -1);
        for (int v = 0; v < n; ++v) if (degree[v]) index[v] = k++;
        if (k == 0) return factor;
    }
    vector<vector<mint>> laplacian(k - 1, vector<mint>(k - 1));
    for (auto [u, v, weight] : edges) {
        if (u == v) continue;
        if (k != n) {
            u = index[u];
            v = index[v];
            if (u < 0 || v < 0) continue;
        }
        if (u < k - 1) laplacian[u][u] += weight;
        if (v < k - 1) laplacian[v][v] += weight;
        if (u < k - 1 && v < k - 1) {
            laplacian[u][v] -= weight;
            laplacian[v][u] -= weight;
        }
    }
    return factor * matrix_determinant(std::move(laplacian));
}

#endif

/**
 * @brief 無向グラフの全域木数
 */
