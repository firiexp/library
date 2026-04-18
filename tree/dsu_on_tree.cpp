struct DSUonTree {
    int n, root;
    vector<pair<int, int>> edges;
    vector<int> start, to;
    vector<int> parent, sub_size, heavy;
    vector<int> euler, down, up;

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
        return down[v];
    }

    int begin(int v) const {
        return down[v];
    }

    int end(int v) const {
        return up[v];
    }

    template<class UPDATE, class QUERY, class CLEAR, class RESET>
    void run(UPDATE update, QUERY query, CLEAR clear, RESET reset) const {
        auto dfs = [&](auto &&self, int v, bool keep) -> void {
            for (int ei = start[v]; ei < start[v + 1]; ++ei) {
                int u = to[ei];
                if (u == parent[v] || u == heavy[v]) continue;
                self(self, u, false);
            }
            if (heavy[v] != -1) self(self, heavy[v], true);
            for (int ei = start[v]; ei < start[v + 1]; ++ei) {
                int u = to[ei];
                if (u == parent[v] || u == heavy[v]) continue;
                for (int i = down[u]; i < up[u]; ++i) update(euler[i]);
            }
            update(v);
            query(v);
            if (!keep) {
                for (int i = down[v]; i < up[v]; ++i) clear(euler[i]);
                reset();
            }
        };
        dfs(dfs, root, false);
    }

private:
    void build_dfs() {
        parent.assign(n, -1);
        sub_size.assign(n, 0);
        heavy.assign(n, -1);
        down.assign(n, 0);
        up.assign(n, 0);
        euler.assign(n, 0);
        int ord = 0;
        auto dfs = [&](auto &&self, int v) -> void {
            sub_size[v] = 1;
            down[v] = ord;
            euler[ord++] = v;
            for (int ei = start[v]; ei < start[v + 1]; ++ei) {
                int u = to[ei];
                if (u == parent[v]) continue;
                parent[u] = v;
                self(self, u);
                sub_size[v] += sub_size[u];
                if (heavy[v] == -1 || sub_size[u] > sub_size[heavy[v]]) {
                    heavy[v] = u;
                }
            }
            up[v] = ord;
        };
        dfs(dfs, root);
    }
};

/**
 * @brief DSU on Tree
 */
