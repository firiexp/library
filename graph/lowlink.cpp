class LowLink {
    void dfs(int i, int p, int &pos){
        ord[i] = low[i] = pos++;
        int ch = 0, mul = 0;
        bool is_art = false;
        for (auto &&j : G[i]) {
            if(j == p && !mul){
                mul = 1;
                continue;
            }
            if(~ord[j]){
                low[i] = min(low[i], ord[j]);
                continue;
            }
            par[j] = i;
            ch++;
            dfs(j, i, pos);
            low[i] = min(low[i], low[j]);
            if(p != -1 && ord[i] <= low[j]) is_art = true;
            if(ord[i] < low[j]) bridge.emplace_back(min(i, j), max(i, j));
        }
        if(p == -1 && ch > 1) is_art = true;
        cut[i] = is_art;
    }
public:
    vector<int> ord, low, par, articulation;
    vector<pair<int, int>> bridge;
    vector<char> cut;
    vector<vector<int>> G;
    LowLink() = default;
    explicit LowLink(int n): ord(n, -1), low(n), par(n, -1), cut(n), G(n){}

    void add_edge(int u, int v){
        if(u != v){
            G[u].emplace_back(v);
            G[v].emplace_back(u);
        }
    }

    void build(){
        int n = G.size(), pos = 0;
        fill(ord.begin(), ord.end(), -1);
        fill(par.begin(), par.end(), -1);
        fill(cut.begin(), cut.end(), 0);
        articulation.clear();
        bridge.clear();
        for (int i = 0; i < n; ++i) {
            if(!~ord[i]) dfs(i, -1, pos);
        }
        for (int i = 0; i < n; ++i) {
            if(cut[i]) articulation.emplace_back(i);
        }
        sort(bridge.begin(), bridge.end());
    }

    inline bool is_bridge(int i, int j){
        if(ord[i] > ord[j]) swap(i, j);
        return ord[i] < low[j];
    }
};
