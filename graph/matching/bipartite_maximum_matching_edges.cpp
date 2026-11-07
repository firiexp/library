#include "hopcroft_karp.cpp"
#include "../connectivity/SCC.cpp"

pair<int, vector<int>> bipartite_maximum_matching_edges(
    int l, int r, const vector<pair<int, int>> &edges) {
    HopcroftKarp matching(l, r);
    for (auto [u, v] : edges) matching.add_edge(u, v);
    int size = matching.max_matching();

    vector<int> right_id = matching.match_right;
    int n = l;
    for (int &v : right_id) if (v == -1) v = n++;
    SCC scc(n);
    vector<int> chosen(l, -1);
    vector<char> parallel(l);
    for (int id = 0; id < int(edges.size()); ++id) {
        auto [u, v] = edges[id];
        if (matching.match_left[u] == v && chosen[u] == -1) {
            chosen[u] = id;
        } else {
            int w = right_id[v];
            if (u == w) parallel[u] = true;
            else scc.add_edge(u, w);
        }
    }
    bool has_unmatched = size < l || size < r;
    int k = scc.build(has_unmatched);
    vector<char> from_left(k), to_right(k);
    if (has_unmatched) {
        for (int u = 0; u < l; ++u) {
            if (matching.match_left[u] == -1) from_left[scc[u]] = true;
        }
        for (int v = 0; v < r; ++v) {
            if (matching.match_right[v] == -1) to_right[scc[right_id[v]]] = true;
        }
        for (int c = 0; c < k; ++c) {
            if (from_left[c]) {
                for (int to : scc.G_out[c]) from_left[to] = true;
            }
        }
        for (int c = k - 1; c >= 0; --c) {
            for (int to : scc.G_out[c]) to_right[c] |= to_right[to];
        }
    }

    vector<int> result(edges.size());
    for (int id = 0; id < int(edges.size()); ++id) {
        auto [u, v] = edges[id];
        int a = scc[u], b = scc[right_id[v]];
        if (chosen[u] == id) {
            result[id] = scc.sz[a] == 1 && !parallel[u] && !from_left[a] && !to_right[a] ? 2 : 1;
        } else if (a == b || from_left[a] || to_right[b]) {
            result[id] = 1;
        }
    }
    return {size, move(result)};
}

/**
 * @brief 二部グラフの最大マッチングの辺分類
 */
