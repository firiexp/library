#ifndef FIRIEXP_LIBRARY_GRAPH_EDGE_FAILURE_CONNECTIVITY_CPP
#define FIRIEXP_LIBRARY_GRAPH_EDGE_FAILURE_CONNECTIVITY_CPP

#include "twoedgeconnectedcomponents.cpp"

class EdgeFailureConnectivity {
    TwoEdgeConnectedComponents tecc;
    vector<int> edge_ids, child, component;
    bool built = false;

    bool in_subtree(int root, int v) const {
        return tecc.ord[root] <= tecc.ord[v] && tecc.ord[v] < tecc.ord[root] + tecc.size[root];
    }

public:
    explicit EdgeFailureConnectivity(int n) : tecc(n), component(n) {}

    int add_edge(int u, int v) {
        assert(0 <= u && u < (int)component.size());
        assert(0 <= v && v < (int)component.size());
        edge_ids.push_back(u == v ? -1 : (int)tecc.edges.size());
        tecc.add_edge(u, v);
        built = false;
        return (int)edge_ids.size() - 1;
    }

    void build() {
        tecc.build();
        int n = component.size();
        vector<int> order(n);
        for (int v = 0; v < n; ++v) order[tecc.ord[v]] = v;
        for (int v : order) component[v] = tecc.par[v] < 0 ? v : component[tecc.par[v]];
        child.assign(edge_ids.size(), -1);
        for (int e = 0; e < (int)edge_ids.size(); ++e) {
            int id = edge_ids[e];
            if (id < 0 || !tecc.is_bridge_edge(id)) continue;
            auto [u, v] = tecc.edges[id];
            child[e] = tecc.ord[u] < tecc.ord[v] ? v : u;
        }
        built = true;
    }

    bool connected_without_edge(int u, int v, int edge_id) const {
        assert(built);
        assert(0 <= u && u < (int)component.size());
        assert(0 <= v && v < (int)component.size());
        assert(0 <= edge_id && edge_id < (int)edge_ids.size());
        if (component[u] != component[v]) return false;
        int c = child[edge_id];
        if (c < 0) return true;
        return in_subtree(c, u) == in_subtree(c, v);
    }

    int component_size_without_edge(int u, int edge_id) const {
        assert(built);
        assert(0 <= u && u < (int)component.size());
        assert(0 <= edge_id && edge_id < (int)edge_ids.size());
        int root = component[u], c = child[edge_id];
        if (c < 0 || component[c] != root) return tecc.size[root];
        return in_subtree(c, u) ? tecc.size[c] : tecc.size[root] - tecc.size[c];
    }
};

#endif

/**
 * @brief 辺除去後の連結判定
 */
