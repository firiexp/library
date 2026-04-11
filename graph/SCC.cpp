class SCC {
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

public:
    vector<vector<int>> G_out;
    vector<int> vs, used, cmp, sz;
    SCC() = default;
    explicit SCC(int n) : n(n), used(n), cmp(n), sz(n) {}

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
        fill(used.begin(), used.end(), 0);
        sz.resize(n);
        fill(sz.begin(), sz.end(), 0);
        int k = 0;
        auto dfs_r = [&](auto &&self, int v, int c) -> void {
            used[v] = 1;
            cmp[v] = c;
            sz[c]++;
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
        G_out.assign(k, {});
        sz.resize(k);
        for (auto &&[a, b] : edges) {
            if(cmp[a] != cmp[b]){
                G_out[cmp[a]].emplace_back(cmp[b]);
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

/**
 * @brief 強連結成分分解(SCC)
 */
