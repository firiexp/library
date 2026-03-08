class JumpOnTree {
    int logn;
    vector<vector<int>> up;

public:
    int n;
    vector<vector<int>> G;
    vector<int> depth;

    explicit JumpOnTree(int n) : logn(0), n(n), G(n), depth(n, -1) {}

    void add_edge(int u, int v) {
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }

    void build(int root = 0) {
        logn = 1;
        while ((1 << logn) <= n) ++logn;
        up.assign(logn, vector<int>(n, -1));
        vector<int> st = {root};
        depth[root] = 0;
        while (!st.empty()) {
            int v = st.back();
            st.pop_back();
            for (int to : G[v]) {
                if (to == up[0][v]) continue;
                up[0][to] = v;
                depth[to] = depth[v] + 1;
                st.push_back(to);
            }
        }
        for (int k = 0; k + 1 < logn; ++k) {
            for (int v = 0; v < n; ++v) {
                int p = up[k][v];
                up[k + 1][v] = (p == -1 ? -1 : up[k][p]);
            }
        }
    }

    int ancestor(int v, int k) const {
        if (k > depth[v]) return -1;
        for (int i = 0; i < logn; ++i) {
            if (k >> i & 1) v = up[i][v];
        }
        return v;
    }

    int lca(int u, int v) const {
        if (depth[u] < depth[v]) swap(u, v);
        u = ancestor(u, depth[u] - depth[v]);
        if (u == v) return u;
        for (int k = logn - 1; k >= 0; --k) {
            if (up[k][u] == up[k][v]) continue;
            u = up[k][u];
            v = up[k][v];
        }
        return up[0][u];
    }

    int dist(int u, int v) const {
        int w = lca(u, v);
        return depth[u] + depth[v] - 2 * depth[w];
    }

    int jump(int s, int t, int k) const {
        int w = lca(s, t);
        int a = depth[s] - depth[w];
        int b = depth[t] - depth[w];
        if (k > a + b) return -1;
        if (k <= a) return ancestor(s, k);
        return ancestor(t, a + b - k);
    }
};

/**
 * @brief Jump on Tree
 * @docs _md/jump_on_tree.md
 */
