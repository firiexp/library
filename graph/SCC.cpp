struct SCC {
    vector<vector<int>> G, G_r, G_out;
    vector<int> vs, used, cmp;
    SCC() = default;
    explicit SCC(int n) : G(n), G_r(n), G_out(n), used(n), cmp(n) {}

    void add_edge(int a, int b){
        G[a].emplace_back(b);
        G_r[b].emplace_back(a);
    }

    void dfs(int v){
        used[v] = 1;
        for (auto &&u : G[v]) if(!used[u]) dfs(u);
        vs.emplace_back(v);
    }

    void dfs_r(int v, int k){
        used[v] = 1;
        cmp[v] = k;
        for (auto &&u : G_r[v]) if(!used[u]) dfs_r(u, k);
    }

    int build() {
        int n = G.size();
        for (int i = 0; i < n; ++i) if(!used[i]) dfs(i);
        fill(used.begin(),used.end(), 0);
        int k = 0;
        for (int i = n - 1; i >= 0; --i) {
            if(!used[vs[i]]){
                dfs_r(vs[i], k++);
            }
        }
        G_out.resize(k);
        for (int i = 0; i < n; ++i) {
            for (auto &&j : G[i]) {
                if(cmp[i] != cmp[j]){
                    G_out[cmp[i]].emplace_back(cmp[j]);
                }
            }
        }
        for (int i = 0; i < k; ++i) {
            sort(G_out.begin(), G_out.end());
            G_out.erase(unique(G_out.begin(), G_out.end()), G_out.end());
        }
        return k;
    }

    int operator[](int k) const { return cmp[k]; }
};
