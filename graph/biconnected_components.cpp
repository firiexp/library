class BiconnectedComponents {
    struct CSR {
        vector<int> start, elist;

        CSR() = default;

        CSR(int n, const vector<pair<int, int>> &edges) : start(n + 1), elist(edges.size() * 2) {
            for (auto &&[u, v] : edges) {
                ++start[u + 1];
                ++start[v + 1];
            }
            for (int i = 0; i < n; ++i) start[i + 1] += start[i];
            auto counter = start;
            for (int id = 0; id < (int)edges.size(); ++id) {
                auto &&[u, v] = edges[id];
                elist[counter[u]++] = id;
                elist[counter[v]++] = id;
            }
        }
    };

    int n = 0;
    vector<int> st;

    int other(int id, int v) const {
        return edges[id].first ^ edges[id].second ^ v;
    }

    void dfs(int i, int pe, const CSR &G, int &pos){
        ord[i] = low[i] = pos++;
        for (int ei = G.start[i]; ei < G.start[i + 1]; ++ei) {
            int id = G.elist[ei];
            if(id == pe) continue;
            int j = other(id, i);
            if(ord[j] < ord[i]) st.emplace_back(id);
            if(~ord[j]){
                low[i] = min(low[i], ord[j]);
                continue;
            }
            par[j] = i;
            dfs(j, id, G, pos);
            low[i] = min(low[i], low[j]);
            if(ord[i] <= low[j]){
                bcc_edges.emplace_back();
                while(true){
                    int k = st.back();
                    st.pop_back();
                    bcc_edges.back().emplace_back(min(edges[k].first, edges[k].second), max(edges[k].first, edges[k].second));
                    if(k == id) break;
                }
            }
        }
    }
public:
    vector<int> ord, low, par;
    vector<pair<int, int>> edges;
    vector<vector<pair<int, int>>> bcc_edges;
    vector<vector<int>> bcc_vertices;
    explicit BiconnectedComponents(int n): n(n), ord(n, -1), low(n), par(n, -1){}

    void add_edge(int u, int v){
        if(u == v) return;
        edges.emplace_back(u, v);
    }

    int build(){
        CSR G(n, edges);
        int pos = 0;
        fill(ord.begin(), ord.end(), -1);
        fill(par.begin(), par.end(), -1);
        bcc_edges.clear();
        bcc_vertices.clear();
        st.clear();
        for (int i = 0; i < n; ++i) {
            if(ord[i] < 0) dfs(i, -1, G, pos);
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
            if(G.start[i] == G.start[i + 1]){
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
