#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
template<class T> constexpr T INF = numeric_limits<T>::max() / 4;
#include "../graph/spanning_tree/mst_sensitivity.cpp"
#include "../graph/spanning_tree/kruskal.cpp"
#include "../graph/shortest_path/dijkstra.cpp"

int main() {
    vector<KruskalEdge<int>> edges{{0, 1, 2}, {0, 1, 1}, {1, 2, 3}, {0, 2, 7}};
    vector<vector<edge<int>>> graph(3);
    for (const auto &e : edges) {
        graph[e.from].emplace_back(e.from, e.to, e.cost);
        graph[e.to].emplace_back(e.to, e.from, e.cost);
    }
    assert((dijkstra(0, graph) == vector<int>{0, 1, 4}));
    auto mst = kruskal(edges, 3);
    assert(mst.exists && mst.cost == 4);
    assert((mst.edge_id == vector<int>{1, 2}));
    vector<KruskalEdge<long long>> weighted;
    for (const auto &e : edges) weighted.emplace_back(e.from, e.to, e.cost, 100);
    auto sensitivity = mst_sensitivity(3, weighted);
    assert(sensitivity.exists && sensitivity.cost == 4);
    assert((sensitivity.forced == vector<optional<long long>>{5, 4, 4, 8}));
    assert((sensitivity.forbidden == vector<optional<long long>>{4, 5, 8, 4}));
}
