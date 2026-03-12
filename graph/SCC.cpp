class SCC {
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
        vs.clear();
        fill(used.begin(), used.end(), 0);
        for (int i = 0; i < n; ++i) {
            if (used[i]) continue;
            vector<pair<int, int>> st = {{i, 0}};
            used[i] = 1;
            while (!st.empty()) {
                int v = st.back().first;
                int &it = st.back().second;
                if (it == (int)G[v].size()) {
                    vs.emplace_back(v);
                    st.pop_back();
                    continue;
                }
                int u = G[v][it++];
                if (used[u]) continue;
                used[u] = 1;
                st.emplace_back(u, 0);
            }
        }
        fill(used.begin(),used.end(), 0);
        int k = 0;
        sz.assign(n, 0);
        for (int i = n - 1; i >= 0; --i) {
            if(!used[vs[i]]){
                vector<int> st = {vs[i]};
                used[vs[i]] = 1;
                while (!st.empty()) {
                    int v = st.back();
                    st.pop_back();
                    cmp[v] = k;
                    sz[k]++;
                    for (auto &&u : G_r[v]) {
                        if (used[u]) continue;
                        used[u] = 1;
                        st.emplace_back(u);
                    }
                }
                ++k;
            }
        }
        G_out.assign(k, {});
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

/**
 * @brief 強連結成分分解(SCC)
 */
