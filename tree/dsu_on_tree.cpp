struct DSUonTree {
    int n, root;
    vector<pair<int, int>> edges;
    vector<int> start, to;
    vector<int> sub_size, heavy;
    vector<int> order, dfn;

    explicit DSUonTree(int n = 0) : n(n), root(0) {
        edges.reserve(max(0, n - 1));
    }

    template<class G>
    explicit DSUonTree(const vector<vector<G>> &g, int root = 0) : DSUonTree((int)g.size()) {
        vector<int> parent(n, -2);
        vector<int> st(1, root);
        parent[root] = -1;
        while (!st.empty()) {
            int v = st.back();
            st.pop_back();
            for (auto &&u : g[v]) {
                if (u == parent[v] || parent[u] != -2) continue;
                parent[u] = v;
                edges.emplace_back(v, u);
                st.push_back(u);
            }
        }
        build(root);
    }

    void add_edge(int u, int v) {
        edges.emplace_back(u, v);
    }

    void build(int root = 0) {
        this->root = root;
        start.assign(n + 1, 0);
        to.assign(edges.size() * 2, 0);
        for (auto &&[u, v] : edges) {
            ++start[u + 1];
            ++start[v + 1];
        }
        for (int i = 0; i < n; ++i) start[i + 1] += start[i];
        auto counter = start;
        for (auto &&[u, v] : edges) {
            to[counter[u]++] = v;
            to[counter[v]++] = u;
        }
        build_dfs();
    }

    int idx(int v) const {
        return dfn[v];
    }

    int begin(int v) const {
        return dfn[v];
    }

    int end(int v) const {
        return dfn[v] + sub_size[v];
    }

    template<class ADD, class QUERY, class REMOVE>
    void run_add_remove(ADD add, QUERY query, REMOVE remove) const {
        auto dfs = [&](auto &&self, int v, int p, bool keep) -> void {
            for (int ei = start[v]; ei < start[v + 1]; ++ei) {
                int u = to[ei];
                if (u == p || u == heavy[v]) continue;
                self(self, u, v, false);
            }
            if (heavy[v] != -1) self(self, heavy[v], v, true);
            for (int ei = start[v]; ei < start[v + 1]; ++ei) {
                int u = to[ei];
                if (u == p || u == heavy[v]) continue;
                for (int i = dfn[u]; i < dfn[u] + sub_size[u]; ++i) add(order[i]);
            }
            add(v);
            query(v);
            if (!keep) {
                for (int i = dfn[v]; i < dfn[v] + sub_size[v]; ++i) remove(order[i]);
            }
        };
        dfs(dfs, root, -1, false);
    }

    template<class ADD, class QUERY, class RESET>
    void run_add_reset(ADD add, QUERY query, RESET reset) const {
        int L = 0, R = 0;
        for (int i = n - 1; i >= 0; --i) {
            int v = order[i];
            if (sub_size[v] == 1) {
                reset();
                L = R = dfn[v];
            }
            while (L > dfn[v]) add(order[--L]);
            while (R < dfn[v] + sub_size[v]) add(order[R++]);
            query(v);
        }
        reset();
    }

private:
    void build_dfs() {
        sub_size.assign(n, 0);
        heavy.assign(n, -1);
        auto dfs_size = [&](auto &&self, int v, int p) -> void {
            sub_size[v] = 1;
            for (int ei = start[v]; ei < start[v + 1]; ++ei) {
                int u = to[ei];
                if (u == p) continue;
                self(self, u, v);
                sub_size[v] += sub_size[u];
                if (heavy[v] == -1 || sub_size[u] > sub_size[heavy[v]]) {
                    heavy[v] = u;
                }
            }
        };
        dfs_size(dfs_size, root, -1);
        dfn.assign(n, 0);
        order.clear();
        order.reserve(n);
        auto dfs_order = [&](auto &&self, int v, int p) -> void {
            dfn[v] = (int)order.size();
            order.push_back(v);
            if (heavy[v] != -1) self(self, heavy[v], v);
            for (int ei = start[v]; ei < start[v + 1]; ++ei) {
                int u = to[ei];
                if (u == p || u == heavy[v]) continue;
                self(self, u, v);
            }
        };
        dfs_order(dfs_order, root, -1);
    }
};

/**
 * @brief DSU on Tree
 */
