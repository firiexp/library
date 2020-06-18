class Bipartite_Matching {
protected:
    vector<vector<int>> G;
    vector<int> used, alive;
    int t;
    int l, r;
public:
    vector<int> match;
    explicit Bipartite_Matching(int l, int r): l(l), r(r), t(0), G(l+r), used(l+r, 0), alive(l+r, -1), match(l+r, -1) {};

    void add_edge(int a, int b){
        G[a].emplace_back(b+l);
        G[b+l].emplace_back(a);
    }

    bool dfs(int x){
        used[x] = t;
        for (auto &&i : G[x]) {
            int w = match[i];
            if(alive[i] == 0) continue;
            if(w == -1 || (used[w] != t && dfs(w))){
                match[x] = i;
                match[i] = x;
                return true;
            }
        }
        return false;
    }

    int matching() {
        int ans = 0;
        for (int i = 0; i < G.size(); ++i) {
            if(alive[i] == 0) continue;
            if(match[i] == -1) {
                ++t;
                ans += dfs(i);
            }
        }
        return ans;
    }
};

/**
 * @brief 二部グラフの最大マッチング
 * @docs _md/bipartite_matching.md
 */
