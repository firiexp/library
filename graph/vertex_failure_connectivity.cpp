#include "block_cut_tree.cpp"
#include "../tree/hld.cpp"

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
        int a = bct.id[u], b = bct.id[v], c = bct.id[x];
        if (hld.tree_id[a] != hld.tree_id[b]) return false;
        if (!bct.is_articulation[x] || hld.tree_id[a] != hld.tree_id[c]) return true;
        return hld.distance(a, b) != hld.distance(a, c) + hld.distance(c, b);
    }
};

/**
 * @brief 頂点除去後の連結判定
 */
