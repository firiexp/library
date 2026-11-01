#include "hopcroft_karp.cpp"

vector<vector<int>> dag_minimum_path_cover(const vector<vector<int>> &g) {
    int n = g.size();
    HopcroftKarp matching(n, n);
    for (int v = 0; v < n; ++v) {
        for (int to : g[v]) matching.add_edge(v, to);
    }
    int size = matching.max_matching();
    vector<vector<int>> paths;
    paths.reserve(n - size);
    for (int v = 0; v < n; ++v) {
        if (matching.match_right[v] != -1) continue;
        paths.emplace_back();
        for (int u = v; u != -1; u = matching.match_left[u]) paths.back().push_back(u);
    }
    return paths;
}

/**
 * @brief DAGの最小頂点素パス被覆
 */
