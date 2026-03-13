class JumpOnTree {
    int logn;
    vector<int> up;

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
        up.assign(logn * n, -1);
        fill(depth.begin(), depth.end(), -1);
        vector<int> offset(n + 1);
        for (int v = 0; v < n; ++v) offset[v + 1] = offset[v] + (int)G[v].size();
        vector<int> to(offset[n]);
        for (int v = 0; v < n; ++v) {
            int ptr = offset[v];
            for (int u : G[v]) to[ptr++] = u;
        }
        vector<int> st;
        st.reserve(n);
        st.push_back(root);
        depth[root] = 0;
        while (!st.empty()) {
            int v = st.back();
            st.pop_back();
            int pv = up[v];
            for (int i = offset[v]; i < offset[v + 1]; ++i) {
                int u = to[i];
                if (u == pv) continue;
                up[u] = v;
                depth[u] = depth[v] + 1;
                st.push_back(u);
            }
        }
        for (int k = 0; k + 1 < logn; ++k) {
            const int *cur = up.data() + k * n;
            int *nxt = up.data() + (k + 1) * n;
            for (int v = 0; v < n; ++v) {
                int p = cur[v];
                nxt[v] = (p == -1 ? -1 : cur[p]);
            }
        }
    }

    int ancestor(int v, int k) const {
        if (k > depth[v]) return -1;
        const int *row = up.data();
        while (k) {
            if (k & 1) v = row[v];
            row += n;
            k >>= 1;
        }
        return v;
    }

    int lca(int u, int v) const {
        if (depth[u] < depth[v]) swap(u, v);
        u = ancestor(u, depth[u] - depth[v]);
        if (u == v) return u;
        const int *row = up.data() + (logn - 1) * n;
        for (int k = logn - 1; k >= 0; --k, row -= n) {
            if (row[u] == row[v]) continue;
            u = row[u];
            v = row[v];
        }
        return up[u];
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
 */
