class GeneralMatching {
    int n;
    vector<vector<int>> g;
    vector<int> match, parent, base, q;
    vector<bool> used, blossom;

    int lca(int a, int b) {
        vector<bool> seen(n, false);
        while (true) {
            a = base[a];
            seen[a] = true;
            if (match[a] == -1) break;
            a = parent[match[a]];
        }
        while (true) {
            b = base[b];
            if (seen[b]) return b;
            if (match[b] == -1) break;
            b = parent[match[b]];
        }
        return -1;
    }

    void mark_path(int v, int b, int child) {
        while (base[v] != b) {
            blossom[base[v]] = blossom[base[match[v]]] = true;
            parent[v] = child;
            child = match[v];
            v = parent[match[v]];
        }
    }

    int find_path(int root) {
        fill(used.begin(), used.end(), false);
        fill(parent.begin(), parent.end(), -1);
        for (int i = 0; i < n; ++i) base[i] = i;
        int head = 0, tail = 0;
        q[tail++] = root;
        used[root] = true;
        while (head < tail) {
            int v = q[head++];
            for (int to : g[v]) {
                if (base[v] == base[to] || match[v] == to) continue;
                if (to == root || (match[to] != -1 && parent[match[to]] != -1)) {
                    int cur = lca(v, to);
                    fill(blossom.begin(), blossom.end(), false);
                    mark_path(v, cur, to);
                    mark_path(to, cur, v);
                    for (int i = 0; i < n; ++i) {
                        if (!blossom[base[i]]) continue;
                        base[i] = cur;
                        if (used[i]) continue;
                        used[i] = true;
                        q[tail++] = i;
                    }
                } else if (parent[to] == -1) {
                    parent[to] = v;
                    if (match[to] == -1) return to;
                    int u = match[to];
                    used[u] = true;
                    q[tail++] = u;
                }
            }
        }
        return -1;
    }

public:
    explicit GeneralMatching(int n)
        : n(n), g(n), match(n, -1), parent(n), base(n), q(n), used(n), blossom(n) {}

    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int max_matching() {
        int res = 0;
        for (int i = 0; i < n; ++i) {
            if (match[i] != -1) continue;
            int v = find_path(i);
            if (v == -1) continue;
            ++res;
            while (v != -1) {
                int pv = parent[v];
                int nv = pv == -1 ? -1 : match[pv];
                match[v] = pv;
                if (pv != -1) match[pv] = v;
                v = nv;
            }
        }
        return res;
    }

    const vector<int>& get_match() const {
        return match;
    }

    vector<pair<int, int>> get_pairs() const {
        vector<pair<int, int>> res;
        for (int i = 0; i < n; ++i) {
            if (match[i] == -1 || i > match[i]) continue;
            res.emplace_back(i, match[i]);
        }
        return res;
    }
};

/**
 * @brief 一般グラフ最大マッチング(General Matching)
 */
