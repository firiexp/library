struct SCC {
    struct CSR {
        vector<int> start, elist;

        CSR() = default;

        CSR(int n, const vector<pair<int, int>> &edges, bool rev) : start(n + 1), elist(edges.size()) {
            for (auto &&[a, b] : edges) {
                ++start[(rev ? b : a) + 1];
            }
            for (int i = 0; i < n; ++i) start[i + 1] += start[i];
            auto counter = start;
            for (auto &&[a, b] : edges) {
                int from = rev ? b : a;
                int to = rev ? a : b;
                elist[counter[from]++] = to;
            }
        }
    };

    int n = 0;
    vector<pair<int, int>> edges;
    vector<int> vs, used, cmp;
    SCC() = default;
    explicit SCC(int n) : n(n), used(n), cmp(n) {}

    void add_edge(int a, int b){
        edges.emplace_back(a, b);
    }

    int build() {
        CSR G(n, edges, false), G_r(n, edges, true);
        vs.clear();
        vs.reserve(n);
        fill(used.begin(), used.end(), 0);
        auto dfs = [&](auto &&self, int v) -> void {
            used[v] = 1;
            for (int ei = G.start[v]; ei < G.start[v + 1]; ++ei) {
                int u = G.elist[ei];
                if(!used[u]) self(self, u);
            }
            vs.emplace_back(v);
        };
        for (int i = 0; i < n; ++i) {
            if(!used[i]) dfs(dfs, i);
        }
        fill(used.begin(),used.end(), 0);
        int k = 0;
        auto dfs_r = [&](auto &&self, int v, int c) -> void {
            used[v] = 1;
            cmp[v] = c;
            for (int ei = G_r.start[v]; ei < G_r.start[v + 1]; ++ei) {
                int u = G_r.elist[ei];
                if(!used[u]) self(self, u, c);
            }
        };
        for (int i = n - 1; i >= 0; --i) {
            if(!used[vs[i]]){
                dfs_r(dfs_r, vs[i], k++);
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

/**
 * @brief 2-SAT
 */
