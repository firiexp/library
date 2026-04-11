using namespace std;

#include "twoedgeconnectedcomponents.cpp"

struct BridgeTree {
    int n, component_count;
    TwoEdgeConnectedComponents tecc;
    vector<vector<int>> tree, nodes;
    vector<pair<int, int>> edges;
    vector<int> id;

    explicit BridgeTree(int n) : n(n), component_count(0), tecc(n), id(n, -1) {}

    void add_edge(int u, int v) {
        tecc.add_edge(u, v);
    }

    int build() {
        component_count = tecc.build();
        id = tecc.bridge;
        nodes = tecc.out;
        tree.assign(component_count, {});
        edges.clear();
        for (int i = 0; i < (int)tecc.edges.size(); ++i) {
            if (!tecc.is_bridge_edge(i)) continue;
            auto [a, b] = tecc.edges[i];
            int u = id[a], v = id[b];
            tree[u].push_back(v);
            tree[v].push_back(u);
            edges.emplace_back(u, v);
        }
        return component_count;
    }
};

/**
 * @brief 橋木(Bridge Tree)
 */
