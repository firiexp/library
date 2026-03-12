class BiconnectedComponents {
    vector<int> st;
public:
    vector<int> ord, low, par;
    vector<pair<int, int>> edges;
    vector<vector<pair<int, int>>> G;
    vector<vector<pair<int, int>>> bcc_edges;
    vector<vector<int>> bcc_vertices;
    explicit BiconnectedComponents(int n): ord(n, -1), low(n), par(n, -1), G(n){}

    void add_edge(int u, int v){
        if(u != v){
            int id = edges.size();
            edges.emplace_back(u, v);
            G[u].emplace_back(v, id);
            G[v].emplace_back(u, id);
        }
    }

    int build(){
        int n = G.size(), pos = 0;
        fill(ord.begin(), ord.end(), -1);
        fill(par.begin(), par.end(), -1);
        bcc_edges.clear();
        bcc_vertices.clear();
        st.clear();
        for (int i = 0; i < n; ++i) {
            if (ord[i] >= 0) continue;
            vector<tuple<int, int, int>> dfs_st = {{i, -1, 0}};
            ord[i] = low[i] = pos++;
            while (!dfs_st.empty()) {
                auto &[v, pe, it] = dfs_st.back();
                if (it == (int)G[v].size()) {
                    dfs_st.pop_back();
                    if (pe != -1) {
                        int p = par[v];
                        low[p] = min(low[p], low[v]);
                        if (ord[p] <= low[v]) {
                            bcc_edges.emplace_back();
                            while (true) {
                                int k = st.back();
                                st.pop_back();
                                bcc_edges.back().emplace_back(min(edges[k].first, edges[k].second), max(edges[k].first, edges[k].second));
                                if (k == pe) break;
                            }
                        }
                    }
                    continue;
                }
                auto [j, id] = G[v][it++];
                if (id == pe) continue;
                if (ord[j] < ord[v]) st.emplace_back(id);
                if (~ord[j]) {
                    low[v] = min(low[v], ord[j]);
                    continue;
                }
                par[j] = v;
                ord[j] = low[j] = pos++;
                dfs_st.emplace_back(j, id, 0);
            }
        }
        vector<int> seen(n, -1);
        bcc_vertices.reserve(bcc_edges.size());
        for (int i = 0; i < (int)bcc_edges.size(); ++i) {
            vector<int> now;
            for (auto &&e : bcc_edges[i]) {
                if(seen[e.first] != i){
                    seen[e.first] = i;
                    now.emplace_back(e.first);
                }
                if(seen[e.second] != i){
                    seen[e.second] = i;
                    now.emplace_back(e.second);
                }
            }
            bcc_vertices.emplace_back(now);
        }
        for (int i = 0; i < n; ++i) {
            if(G[i].empty()){
                bcc_edges.emplace_back();
                bcc_vertices.push_back({i});
            }
        }
        return bcc_vertices.size();
    }
};

/**
 * @brief 二重連結成分分解(Biconnected Components)
 */
