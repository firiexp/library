#include "block_cut_tree.cpp"
#include "../../tree/hld.cpp"

class VertexFailureConnectivity {
    BlockCutTree bct;
    HeavyLightDecomposition hld;

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
};

/**
 * @brief 頂点除去後の連結判定
 */
