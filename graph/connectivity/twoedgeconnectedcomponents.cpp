class TwoEdgeConnectedComponents {
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

    int other(int id, int v) const {
        return edges[id].first ^ edges[id].second ^ v;
    }

    void dfs(int i, int pe, const CSR &G, int &pos){
        ord[i] = low[i] = pos++;
        for (int ei = G.start[i]; ei < G.start[i + 1]; ++ei) {
            int id = G.elist[ei];
            if(id == pe) continue;
            int j = other(id, i);
            if(~ord[j]){
                low[i] = min(low[i], ord[j]);
                continue;
            }
            par[j] = i;
            dfs(j, id, G, pos);
            size[i] += size[j];
            low[i] = min(low[i], low[j]);
        }
    }

    void dfs2(int i, int c, const CSR &G){
        bridge[i] = c;
        out[c].emplace_back(i);
        for (int ei = G.start[i]; ei < G.start[i + 1]; ++ei) {
            int id = G.elist[ei];
            if(is_bridge_edge(id)) continue;
            int j = other(id, i);
            if(~bridge[j]) continue;
            dfs2(j, c, G);
        }
    }
public:
    vector<int> ord, low, par, bridge, size;
    vector<pair<int, int>> edges;
    vector<vector<int>> out;
    explicit TwoEdgeConnectedComponents(int n): n(n), ord(n, -1), low(n), par(n, -1), bridge(n, -1), size(n, 1){}

    inline bool is_bridge(int i, int j){
        if(ord[i] > ord[j]) swap(i, j);
        return ord[i] < low[j];
    }

    bool is_bridge_edge(int id) const {
        auto [u, v] = edges[id];
        if(ord[u] > ord[v]) swap(u, v);
        return ord[u] < low[v];
    }

    void add_edge(int u, int v){
        if(u == v) return;
        edges.emplace_back(u, v);
    }

    int build(){
        CSR G(n, edges);
        int pos = 0;
        fill(ord.begin(), ord.end(), -1);
        fill(par.begin(), par.end(), -1);
        fill(bridge.begin(), bridge.end(), -1);
        fill(size.begin(), size.end(), 1);
        out.clear();
        for (int i = 0; i < n; ++i) {
            if(ord[i] < 0) dfs(i, -1, G, pos);
        }
        int k = 0;
        for (int i = 0; i < n; ++i) {
            if(!~bridge[i]){
                out.emplace_back();
                dfs2(i, k++, G);
            }
        }
        return k;
    }
};

/**
 * @brief 二辺連結成分分解(Two-Edge-Connected Components)
 */
