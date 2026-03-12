struct TreeHash {
    int n;
    vector<vector<int>> g;
    vector<int> parent, order, hash_id;
    int kind_count;

    explicit TreeHash(int n)
        : n(n), g(n), parent(n, -1), hash_id(n, -1), kind_count(0) {}

    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> build(int root = 0) {
        order.clear();
        order.reserve(n);
        parent.assign(n, -1);
        vector<int> st(1, root);
        parent[root] = root;
        while (!st.empty()) {
            int v = st.back();
            st.pop_back();
            order.push_back(v);
            for (int to : g[v]) {
                if (to == parent[v]) continue;
                parent[to] = v;
                st.push_back(to);
            }
        }

        map<vector<int>, int> ids;
        for (int i = n - 1; i >= 0; --i) {
            int v = order[i];
            vector<int> ch;
            ch.reserve(g[v].size() - (v != root));
            for (int to : g[v]) {
                if (to == parent[v]) continue;
                ch.push_back(hash_id[to]);
            }
            sort(ch.begin(), ch.end());
            auto [it, inserted] = ids.emplace(ch, (int)ids.size());
            hash_id[v] = it->second;
        }
        kind_count = ids.size();
        return hash_id;
    }

    int operator[](int v) const {
        return hash_id[v];
    }

    int kinds() const {
        return kind_count;
    }
};

/**
 * @brief 木ハッシュ(Tree Hash)
 */
