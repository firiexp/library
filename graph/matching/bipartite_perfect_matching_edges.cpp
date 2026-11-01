#include "hopcroft_karp.cpp"
#include "../connectivity/SCC.cpp"

vector<int> bipartite_perfect_matching_edges(
    int n, const vector<pair<int, int>> &edges) {
    HopcroftKarp matching(n, n);
    for(auto [u, v] : edges) matching.add_edge(u, v);
    if(matching.max_matching() != n) return {};

    SCC scc(2 * n);
    vector<int> chosen(n, -1);
    for(int id = 0; id < int(edges.size()); ++id) {
        auto [u, v] = edges[id];
        if(matching.match_left[u] == v && chosen[u] == -1) {
            chosen[u] = id;
            scc.add_edge(n + v, u);
        } else {
            scc.add_edge(u, n + v);
        }
    }
    scc.build(false);
    vector<int> result(edges.size());
    for(int id = 0; id < int(edges.size()); ++id) {
        auto [u, v] = edges[id];
        if(scc[u] == scc[n + v]) result[id] = 1;
        else if(chosen[u] == id) result[id] = 2;
    }
    return result;
}

/**
 * @brief 二部グラフの完全マッチングの辺分類
 */
