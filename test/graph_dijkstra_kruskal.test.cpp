#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
template<class T> constexpr T INF = numeric_limits<T>::max() / 4;
#include "../graph/shortest_path/dijkstra.cpp"
#include "../graph/spanning_tree/kruskal.cpp"
#include "../graph/spanning_tree/mst_sensitivity.cpp"

int main() {
    vector<KruskalEdge<long long>> edges{
        {0, 1, 5, 9}, {0, 2, 1}, {2, 1, 2, 7}, {1, 3, 4}, {2, 3, 10}, {3, 3, 0}
    };
    vector<vector<edge<long long>>> graph(4);
    for (const auto &e : edges) {
        graph[e.from].emplace_back(e.to, e.cost);
        graph[e.to].emplace_back(e.from, e.cost);
    }
    assert((dijkstra(0, graph) == vector<long long>{0, 3, 1, 7}));
    auto mst = kruskal(edges, 4);
    assert(mst.exists && mst.cost == 7);
    assert((mst.edge_id == vector<int>{1, 7, 3}));
    assert(edges[1].idx == -1 && edges[2].idx == 7);
    auto sensitivity = mst_sensitivity(4, edges);
    assert(sensitivity.exists && sensitivity.cost == mst.cost);
    assert(sensitivity.forced[0] == 10);
    assert(sensitivity.forbidden[1] == 11);
    assert(!sensitivity.forced[5] && sensitivity.forbidden[5] == 7);
    assert(!kruskal(edges, 5).exists);
}
