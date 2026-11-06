#include "hopcroft_karp.cpp"
#include "../connectivity/SCC.cpp"

vector<int> bipartite_perfect_matching_edges(
    int n, const vector<pair<int, int>> &edges) {
    HopcroftKarp matching(n, n);
    for(auto [u, v] : edges) matching.add_edge(u, v);
    if(matching.max_matching() != n) return {};

    SCC scc(n);
    vector<int> chosen(n, -1);
    vector<char> parallel(n);
    for(int id = 0; id < int(edges.size()); ++id) {
        auto [u, v] = edges[id];
        if(matching.match_left[u] == v && chosen[u] == -1) {
            chosen[u] = id;
        } else {
            int w = matching.match_right[v];
            if(u == w) parallel[u] = true;
            else scc.add_edge(u, w);
        }
    }
    scc.build(false);
    vector<int> result(edges.size());
    for(int id = 0; id < int(edges.size()); ++id) {
        auto [u, v] = edges[id];
        if(chosen[u] == id && scc.sz[scc[u]] == 1 && !parallel[u]) result[id] = 2;
        else if(scc[u] == scc[matching.match_right[v]]) result[id] = 1;
    }
    return result;
}

/**
 * @brief 二部グラフの完全マッチングの辺分類
 */
