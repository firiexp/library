#include "../datastructure/sparsetable.cpp"

struct LCA_MinDepth {
    using T = pair<int, int>;
    static T f(T a, T b) { return min(a, b); }
    static T e() { return T{INF<int>, -1}; }
};

class LCA {
    SparseTable<LCA_MinDepth> table;

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
        vector<int> parent(n, -2), dep(n);
        vector<int> it(n);
        vector<int> st = {root};
        parent[root] = -1;
        while (!st.empty()) {
            int v = st.back();
            if (it[v] == 0) {
                id[v] = k;
                vs[k] = v;
                depth[k++] = dep[v];
            }
            if (it[v] == (int)G[v].size()) {
                st.pop_back();
                if (!st.empty()) {
                    int p = st.back();
                    vs[k] = p;
                    depth[k++] = dep[p];
                }
                continue;
            }
            int u = G[v][it[v]++];
            if (u == parent[v]) continue;
            parent[u] = v;
            dep[u] = dep[v] + 1;
            st.push_back(u);
        }
    }

    void build(int root = 0) {
        eulertour(root);
        vector<pair<int, int>> v(2 * n - 1);
        for (int i = 0; i < 2 * n - 1; ++i) {
            v[i] = make_pair(depth[i], i);
        }
        table.build(v);
    }

    void buildLCA(int root = 0) {
        build(root);
    }

    int lca(int u, int v) {
        if (id[u] > id[v]) swap(u, v);
        return vs[table.query(id[u], id[v] + 1).second];
    }
};

/**
 * @brief 最近共通祖先(LCA)
 */
