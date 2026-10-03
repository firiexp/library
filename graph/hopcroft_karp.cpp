class HopcroftKarp {
    int l, r;
    vector<pair<int, int>> edges;
    vector<int> start, elist;
    vector<int> dist;
    bool dirty = true;

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
        dirty = true;
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
        int ret = 0;
        for (int v : match_left) if (v != -1) ++ret;
        if (!dirty) return ret;
        build_graph();
        while (bfs()) {
            for (int i = 0; i < l; ++i) {
                if (match_left[i] == -1 && dfs(i)) ++ret;
            }
        }
        dirty = false;
        return ret;
    }

    pair<vector<int>, vector<int>> minimum_vertex_cover() {
        max_matching();
        vector<char> seen_left(l), seen_right(r);
        queue<int> q;
        for (int i = 0; i < l; ++i) {
            if (match_left[i] != -1) continue;
            seen_left[i] = true;
            q.push(i);
        }
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int ei = start[v]; ei < start[v + 1]; ++ei) {
                int to = elist[ei];
                if (to == match_left[v] || seen_right[to]) continue;
                seen_right[to] = true;
                int u = match_right[to];
                if (u != -1 && !seen_left[u]) {
                    seen_left[u] = true;
                    q.push(u);
                }
            }
        }
        vector<int> left, right;
        for (int i = 0; i < l; ++i) if (!seen_left[i]) left.push_back(i);
        for (int i = 0; i < r; ++i) if (seen_right[i]) right.push_back(i);
        return {move(left), move(right)};
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
