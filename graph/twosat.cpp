struct SCC {
    vector<vector<int>> G, G_r, G_out;
    vector<int> vs, used, cmp;
    SCC() = default;
    explicit SCC(int n) : G(n), G_r(n), used(n), cmp(n) {}

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
        return k;
    }

    int operator[](int k) const { return cmp[k]; }
};

struct TwoSAT {
    int n;
    SCC scc;
    explicit TwoSAT(int n) : n(n), scc(n*2) {};
    int negate(int v){
        int ret = n+v;
        if(ret >= n*2) ret -= n*2;
        return ret;
    }

    vector<int> build() {
        scc.build();
        vector<int> res(n);
        for (int i = 0; i < n; ++i) {
            if(scc[i] == scc[n+i]) return {};
            res[i] = scc[i] > scc[n+i];
        }
        return res;
    }

    void add_if(int u, int v){ // u -> v
        scc.add_edge(u, v);
        scc.add_edge(negate(v), negate(u));
    }

    void add_or(int u, int v){ // u || v
        add_if(negate(u), v);
    }
};