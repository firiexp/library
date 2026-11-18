#ifndef FIRIEXP_LIBRARY_GRAPH_KRUSKAL_RECONSTRUCTION_TREE_CPP
#define FIRIEXP_LIBRARY_GRAPH_KRUSKAL_RECONSTRUCTION_TREE_CPP

#include "kruskal.cpp"
#include "../../datastructure/unionfind/unionfind.cpp"
#include "../../tree/hld.cpp"

template<class T>
class KruskalReconstructionTree {
    int n;
    vector<T> merge_weight;
    HeavyLightDecomposition forest;

public:
    KruskalReconstructionTree(int n, vector<KruskalEdge<T>> edges) : n(n), forest(0) {
        assert(n >= 0);
        sort(edges.begin(), edges.end(), [](const auto &a, const auto &b) { return a.cost < b.cost; });
        UnionFind uf(n);
        vector<int> top(n), parent(n, -1);
        iota(top.begin(), top.end(), 0);
        for (const auto &e : edges) {
            assert(0 <= e.from && e.from < n && 0 <= e.to && e.to < n);
            auto merge = uf.unite(e.from, e.to);
            if (!merge) continue;
            int v = parent.size();
            parent[top[merge.keep]] = v;
            parent[top[merge.absorbed]] = v;
            parent.push_back(-1);
            top[merge.keep] = v;
            merge_weight.push_back(e.cost);
        }

        forest = HeavyLightDecomposition(parent.size());
        vector<int> roots;
        for (int v = 0; v < (int)parent.size(); ++v) {
            if (parent[v] == -1) roots.push_back(v);
            else forest.add_edge(parent[v], v);
        }
        forest.build(std::move(roots));
    }

    optional<T> connection_threshold(int u, int v) const {
        assert(0 <= u && u < n && 0 <= v && v < n && u != v);
        if (forest.tree_id[u] != forest.tree_id[v]) return nullopt;
        return merge_weight[forest.lca(u, v) - n];
    }
};

#endif

/**
 * @brief 2頂点が初めて連結になる辺重み（Kruskal 再構成木）
 */
