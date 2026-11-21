#include "hld.cpp"

struct HeavyLightDecompositionEdge {
    HeavyLightDecomposition hld;

    explicit HeavyLightDecompositionEdge(int n) : hld(n) {}
    explicit HeavyLightDecompositionEdge(const vector<vector<int>> &g) : hld(g) {}

    void add_edge(int u, int v) {
        hld.add_edge(u, v);
    }

    void build(vector<int> roots = {0}) {
        hld.build(roots);
    }

    int lca(int u, int v) const {
        return hld.lca(u, v);
    }

    int parent(int v) const {
        return hld.parent(v);
    }

    int ancestor(int v, int k) const {
        return hld.ancestor(v, k);
    }

    int distance(int u, int v) const {
        return hld.distance(u, v);
    }

    int jump(int u, int v, int k) const {
        return hld.jump(u, v, k);
    }

    int edge_index(int v) const {
        if (hld.par[v] == -1) return -1;
        return hld.id[v];
    }

    pair<int, int> subtree(int v) const {
        return hld.subtree(v, true);
    }

    template<typename F>
    void path(int u, int v, const F &f) const {
        hld.path(u, v, f, true);
    }

    template<typename F>
    void path_ordered(int u, int v, const F &f) const {
        hld.path_ordered(u, v, f, true);
    }

    template<typename F>
    void apply_subtree(int v, const F &f) const {
        hld.apply_subtree(v, f, true);
    }

    template<typename T, typename Q, typename F>
    T path_query(int u, int v, const T &e, const Q &q, const F &f) const {
        return hld.path_query(u, v, e, q, f, true);
    }

    template<typename T, typename QL, typename QR, typename F>
    T path_query_ordered(int u, int v, const T &e, const QL &ql, const QR &qr, const F &f) const {
        return hld.path_query_ordered(u, v, e, ql, qr, f, true);
    }

    template<typename Q>
    decltype(auto) subtree_query(int v, const Q &q) const {
        return hld.subtree_query(v, q, true);
    }
};

/**
 * @brief HL分解(辺クエリ)
 */
