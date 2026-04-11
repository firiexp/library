class LowLink {
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
        int ch = 0;
        bool is_art = false;
        for (int ei = G.start[i]; ei < G.start[i + 1]; ++ei) {
            int id = G.elist[ei];
            if(id == pe) continue;
            int j = other(id, i);
            if(~ord[j]){
                low[i] = min(low[i], ord[j]);
                continue;
            }
            par[j] = i;
            ch++;
            dfs(j, id, G, pos);
            low[i] = min(low[i], low[j]);
            if(pe != -1 && ord[i] <= low[j]) is_art = true;
            if(ord[i] < low[j]) bridge.emplace_back(min(i, j), max(i, j));
        }
        if(pe == -1 && ch > 1) is_art = true;
        cut[i] = is_art;
    }
public:
    vector<int> ord, low, par, articulation;
    vector<pair<int, int>> bridge;
    vector<pair<int, int>> edges;
    vector<char> cut;
    LowLink() = default;
    explicit LowLink(int n): n(n), ord(n, -1), low(n), par(n, -1), cut(n){}

    void add_edge(int u, int v){
        if(u == v) return;
        edges.emplace_back(u, v);
    }

    void build(){
        CSR G(n, edges);
        int pos = 0;
        fill(ord.begin(), ord.end(), -1);
        fill(par.begin(), par.end(), -1);
        fill(cut.begin(), cut.end(), 0);
        articulation.clear();
        bridge.clear();
        for (int i = 0; i < n; ++i) {
            if(!~ord[i]) dfs(i, -1, G, pos);
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

/**
 * @brief LowLink
 */
