#include "hopcroft_karp.cpp"

vector<int> bipartite_minimum_edge_cover(
    int l, int r, const vector<pair<int, int>> &edges) {
    HopcroftKarp matching(l, r);
    vector<int> incident_left(l, -1), incident_right(r, -1);
    for (int id = 0; id < int(edges.size()); ++id) {
        auto [u, v] = edges[id];
        matching.add_edge(u, v);
        incident_left[u] = incident_right[v] = id;
    }
    for (int id : incident_left) if (id == -1) return {};
    for (int id : incident_right) if (id == -1) return {};

    int size = matching.max_matching();
    vector<int> result;
    result.reserve(l + r - size);
    vector<char> chosen(l);
    for (int id = 0; id < int(edges.size()); ++id) {
        auto [u, v] = edges[id];
        if (matching.match_left[u] != v || chosen[u]) continue;
        chosen[u] = true;
        result.push_back(id);
    }
    for (int u = 0; u < l; ++u) {
        if (matching.match_left[u] == -1) result.push_back(incident_left[u]);
    }
    for (int v = 0; v < r; ++v) {
        if (matching.match_right[v] == -1) result.push_back(incident_right[v]);
    }
    return result;
}

/**
 * @brief 二部グラフの最小辺被覆
 */
