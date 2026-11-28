#include "../datastructure/sparsetable.cpp"

class LCA {
    struct MinParent {
        using T = int;
        static int f(int a, int b) { return min(a, b); }
    };
    SparseTable<MinParent> table;
    vector<int> preorder;

    void dfs_euler(int v, int p, int d, int &k) {
        id[v] = k;
        vs[k] = v;
        depth[k++] = d;
        for (auto &&u : G[v]) {
            if (u == p) continue;
            dfs_euler(u, v, d + 1, k);
            vs[k] = v;
            depth[k++] = d;
        }
    }

public:
    int n;
    vector<vector<int>> G;
    vector<int> vs, depth, id;

    explicit LCA(int n) : table(), n(n), G(n), vs(2 * n - 1), depth(2 * n - 1), id(n) {}

    void add_edge(int a, int b) {
        G[a].emplace_back(b);
        G[b].emplace_back(a);
    }

    void eulertour(int root = 0) {
        int k = 0;
        dfs_euler(root, -1, 0, k);
    }

    void build(int root = 0) {
        eulertour(root);
        preorder.resize(n);
        preorder[root] = 0;
        vector<int> parent_id;
        parent_id.reserve(n - 1);
        for (int i = 1; i < 2 * n - 1; ++i) {
            if (depth[i] < depth[i - 1]) continue;
            parent_id.push_back(id[vs[i - 1]]);
            preorder[vs[i]] = parent_id.size();
        }
        table.build(parent_id);
    }

    void buildLCA(int root = 0) {
        build(root);
    }

    int lca(int u, int v) {
        if (u == v) return u;
        int a = preorder[u], b = preorder[v];
        if (a > b) swap(a, b);
        return vs[table.query(a, b)];
    }
};

/**
 * @brief 最近共通祖先(LCA)
 */
