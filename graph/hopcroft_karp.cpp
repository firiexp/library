class HopcroftKarp {
    int l, r;
    vector<pair<int, int>> edges;
    vector<int> start, elist;
    vector<int> dist;

    void build_graph() {
        start.assign(l + 1, 0);
        elist.assign(edges.size(), 0);
        for (auto &&[a, b] : edges) ++start[a + 1];
        for (int i = 0; i < l; ++i) start[i + 1] += start[i];
        auto counter = start;
        for (auto &&[a, b] : edges) {
            elist[counter[a]++] = b;
        }
    }

public:
    vector<int> match_left, match_right;

    explicit HopcroftKarp(int l, int r) : l(l), r(r), start(l + 1), dist(l), match_left(l, -1), match_right(r, -1) {}

    void add_edge(int a, int b) {
        edges.emplace_back(a, b);
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
            for (int ei = start[v]; ei < start[v + 1]; ++ei) {
                int to = elist[ei];
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
        for (int ei = start[v]; ei < start[v + 1]; ++ei) {
            int to = elist[ei];
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
        build_graph();
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
 * @brief Hopcroft-Karp法
 */
