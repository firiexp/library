#include "hld.cpp"

struct HeavyLightDecompositionEdge {
    HeavyLightDecomposition hld;

    explicit HeavyLightDecompositionEdge(int n) : hld(n) {}
    explicit HeavyLightDecompositionEdge(vector<vector<int>> &g) : hld(g) {}

    void add_edge(int u, int v) {
        hld.add_edge(u, v);
    }

    void build(vector<int> roots = {0}) {
        hld.build(roots);
    }

    int lca(int u, int v) {
        return hld.lca(u, v);
    }

    int parent(int v) const {
        return hld.parent(v);
    }

    int ancestor(int v, int k) {
        return hld.ancestor(v, k);
    }

    int distance(int u, int v) {
        return hld.distance(u, v);
    }

    int edge_index(int v) const {
        if (hld.par[v] == -1) return -1;
        return hld.id[v];
    }

    pair<int, int> subtree(int v) const {
        return hld.subtree(v, true);
    }

    template<typename F>
    void path(int u, int v, const F &f) {
        hld.path(u, v, f, true);
    }

    template<typename F>
    void apply_subtree(int v, const F &f) {
        hld.apply_subtree(v, f, true);
    }

    template<typename T, typename Q, typename F>
    T path_query(int u, int v, const T &e, const Q &q, const F &f) {
        return hld.path_query(u, v, e, q, f, true);
    }

    template<typename T, typename QL, typename QR, typename F>
    T path_query_ordered(int u, int v, const T &e, const QL &ql, const QR &qr, const F &f) {
        return hld.path_query_ordered(u, v, e, ql, qr, f, true);
    }

    template<typename T, typename Q>
    T subtree_query(int v, const Q &q) {
        return hld.subtree_query<T>(v, q, true);
    }
};

/**
 * @brief HL分解(辺クエリ)
 */
