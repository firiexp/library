class Bipartite_Matching {
protected:
    vector<vector<int>> G;
    vector<int> used, alive;
    int t;
    int l, r;

public:
    vector<int> match;

    explicit Bipartite_Matching(int l, int r)
        : G(l), used(l, 0), alive(l + r, -1), t(0), l(l), r(r), match(l + r, -1) {}

    void add_edge(int a, int b) {
        G[a].push_back(b);
    }

    bool dfs(int x) {
        used[x] = t;
        for (int y : G[x]) {
            int ry = y + l;
            if (alive[ry] == 0) continue;
            int w = match[ry];
            if (w != -1 && (alive[w] == 0 || used[w] == t || !dfs(w))) continue;
            match[x] = ry;
            match[ry] = x;
            return true;
        }
        return false;
    }

    int matching() {
        int ans = 0;
        for (int i = 0; i < l; ++i) {
            if (alive[i] == 0 || match[i] != -1) continue;
            ++t;
            ans += dfs(i);
        }
        return ans;
    }

    vector<pair<int, int>> get_pairs() const {
        vector<pair<int, int>> res;
        for (int i = 0; i < l; ++i) {
            if (match[i] == -1) continue;
            res.emplace_back(i, match[i] - l);
        }
        return res;
    }
};

/**
 * @brief 二部グラフ最大マッチング(Bipartite Matching)
 */
