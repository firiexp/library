#include "block_cut_tree.cpp"
#include "../../tree/hld.cpp"

class VertexFailureConnectivity {
    BlockCutTree bct;
    HeavyLightDecomposition hld;
    vector<int> weight_prefix, component_sizes;

public:
    explicit VertexFailureConnectivity(int n) : bct(n), hld(0) {}

    void add_edge(int u, int v) {
        bct.add_edge(u, v);
    }

    void build() {
        int n = bct.build();
        hld = HeavyLightDecomposition(bct.tree);
        vector<char> seen(n);
        vector<int> roots, stack;
        for (int v = 0; v < n; ++v) {
            if (seen[v]) continue;
            roots.push_back(v);
            seen[v] = 1;
            stack.push_back(v);
            while (!stack.empty()) {
                int x = stack.back();
                stack.pop_back();
                for (int u : bct.tree[x]) {
                    if (seen[u]) continue;
                    seen[u] = 1;
                    stack.push_back(u);
                }
            }
        }
        hld.build(roots);
        weight_prefix.assign(n + 1, 0);
        for (int v : bct.id) ++weight_prefix[hld.id[v] + 1];
        for (int i = 0; i < n; ++i) weight_prefix[i + 1] += weight_prefix[i];
        component_sizes.resize(roots.size());
        for (int i = 0; i < int(roots.size()); ++i) {
            auto [l, r] = hld.subtree(roots[i]);
            component_sizes[i] = weight_prefix[r] - weight_prefix[l];
        }
    }

    bool connected_without_vertex(int u, int v, int x) {
        if (u == x || v == x) return false;
        int a = bct.id[u], b = bct.id[v];
        if (hld.tree_id[a] != hld.tree_id[b]) return false;
        if (!bct.is_articulation[x]) return true;
        int c = bct.id[x];
        if (hld.tree_id[a] != hld.tree_id[c]) return true;
        auto [l, r] = hld.subtree(c);
        bool contains_a = l <= hld.id[a] && hld.id[a] < r;
        bool contains_b = l <= hld.id[b] && hld.id[b] < r;
        if (contains_a != contains_b) return false;
        return !contains_a || hld.lca(a, b) != c;
    }

    int component_size_without_vertex(int u, int x) const {
        if (u == x) return 0;
        int a = bct.id[u], c = bct.id[x];
        int size = component_sizes[hld.tree_id[a]];
        if (hld.tree_id[a] != hld.tree_id[c]) return size;
        if (!bct.is_articulation[x]) return size - 1;
        auto [l, r] = hld.subtree(c);
        if (hld.id[a] < l || r <= hld.id[a]) {
            return size - (weight_prefix[r] - weight_prefix[l]);
        }
        int child = hld.ancestor(a, hld.dep[a] - hld.dep[c] - 1);
        auto [cl, cr] = hld.subtree(child);
        return weight_prefix[cr] - weight_prefix[cl];
    }
};

/**
 * @brief 頂点除去後の連結判定
 */
