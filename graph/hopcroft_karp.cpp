class HopcroftKarp {
    int l, r;
    vector<vector<int>> g;
    vector<int> dist;

public:
    vector<int> match_left, match_right;

    explicit HopcroftKarp(int l, int r) : l(l), r(r), g(l), dist(l), match_left(l, -1), match_right(r, -1) {}

    void add_edge(int a, int b) {
        g[a].push_back(b);
    }

    bool bfs() {
        queue<int> q;
        fill(dist.begin(), dist.end(), -1);
        for (int i = 0; i < l; ++i) {
            if (match_left[i] != -1) continue;
            dist[i] = 0;
            q.push(i);
        }
        bool found = false;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int to : g[v]) {
                int u = match_right[to];
                if (u == -1) {
                    found = true;
                    continue;
                }
                if (dist[u] != -1) continue;
                dist[u] = dist[v] + 1;
                q.push(u);
            }
        }
        return found;
    }

    bool dfs(int v) {
        for (int to : g[v]) {
            int u = match_right[to];
            if (u != -1 && (dist[u] != dist[v] + 1 || !dfs(u))) continue;
            match_left[v] = to;
            match_right[to] = v;
            return true;
        }
        dist[v] = -1;
        return false;
    }

    int max_matching() {
        int ret = 0;
        while (bfs()) {
            for (int i = 0; i < l; ++i) {
                if (match_left[i] == -1 && dfs(i)) ++ret;
            }
        }
        return ret;
    }

    vector<pair<int, int>> get_pairs() const {
        vector<pair<int, int>> ret;
        for (int i = 0; i < l; ++i) {
            if (match_left[i] != -1) ret.emplace_back(i, match_left[i]);
        }
        return ret;
    }
};

/**
 * @brief Hopcroft-Karp 法
 * @docs _md/hopcroft_karp.md
 */
