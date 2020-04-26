class TwoEdgeConnectedComponents {
    void dfs(int i, int &pos){
        ord[i] = low[i] = pos++;
        int mul = 0;
        for (auto &&j : G[i]) {
            if(j == par[i] && !mul){
                mul = 1;
                continue;
            }
            if(~ord[j]){
                low[i] = min(low[i], ord[j]);
                continue;
            }
            par[j] = i;
            dfs(j, pos);
            size[i] += size[j];
            low[i] = min(low[i], low[j]);
        }
    }

    void dfs2(int i){
        out[bridge[i]].emplace_back(i);
        for (auto &&j : G[i]) {
            if(~bridge[j] || is_bridge(i, j)) continue;
            bridge[j] = bridge[i];
            dfs2(j);
        }
    }
public:
    vector<int> ord, low, par, bridge, size;
    vector<vector<int>> G, out;
    explicit TwoEdgeConnectedComponents(int n): ord(n, -1), low(n), par(n, -1), bridge(n, -1), size(n, 1), G(n){}

    inline bool is_bridge(int i, int j){
        if(ord[i] > ord[j]) swap(i, j);
        return ord[i] < low[j];
    }

    void add_edge(int u, int v){
        if(u != v){
            G[u].emplace_back(v);
            G[v].emplace_back(u);
        }
    }

    int build(){
        int n = G.size(), pos = 0;
        for (int i = 0; i < n; ++i) {
            if(ord[i] < 0) dfs(i, pos);
        }
        int k = 0;
        for (int i = 0; i < n; ++i) {
            if(!~bridge[i]){
                bridge[i] = k++;
                out.emplace_back();
                dfs2(i);
            }
        }
        return k;
    }
};
