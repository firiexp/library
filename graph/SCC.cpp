class SCC {
    void dfs(int v){
        used[v] = 1;
        for (auto &&u : G[v]) if(!used[u]) dfs(u);
        vs.emplace_back(v);
    }

    void dfs_r(int v, int k){
        used[v] = 1;
        cmp[v] = k;
        sz[k]++;
        for (auto &&u : G_r[v]) if(!used[u]) dfs_r(u, k);
    }
public:
    vector<vector<int>> G, G_r, G_out;
    vector<int> vs, used, cmp, sz;
    SCC() = default;
    explicit SCC(int n) : G(n), G_r(n), G_out(n), used(n), cmp(n), sz(n) {}

    void add_edge(int a, int b){
        G[a].emplace_back(b);
        G_r[b].emplace_back(a);
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
        sz.resize(k);
        for (int i = 0; i < n; ++i) {
            for (auto &&j : G[i]) {
                if(cmp[i] != cmp[j]){
                    G_out[cmp[i]].emplace_back(cmp[j]);
                }
            }
        }
        for (auto &&l : G_out) {
            sort(l.begin(), l.end());
            l.erase(unique(l.begin(), l.end()), l.end());
        }
        return k;
    }

    int operator[](int k) const { return cmp[k]; }
};
