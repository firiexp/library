template<bool directed>
struct EulerianTrail {
    struct Edge {
        int from, to;
    };

    struct Result {
        bool exists;
        vector<int> vertices;
        vector<int> edge_ids;
    };

    int n;
    vector<Edge> edges;
    vector<vector<pair<int, int>>> g;

    explicit EulerianTrail(int n) : n(n), g(n) {}

    int add_edge(int from, int to) {
        int id = (int)edges.size();
        edges.push_back({from, to});
        g[from].push_back({to, id});
        if constexpr (!directed) g[to].push_back({from, id});
        return id;
    }

    Result solve() const {
        int m = edges.size();
        if (m == 0) {
            return {true, {0}, {}};
        }

        vector<int> indeg(n), outdeg(n), deg(n);
        for (auto&& e : edges) {
            ++outdeg[e.from];
            ++indeg[e.to];
            ++deg[e.from];
            ++deg[e.to];
        }

        int start = -1, plus = 0, minus = 0;
        if constexpr (directed) {
            for (int v = 0; v < n; ++v) {
                int diff = outdeg[v] - indeg[v];
                if (diff == 1) {
                    start = v;
                    ++plus;
                } else if (diff == -1) {
                    ++minus;
                } else if (diff != 0) {
                    return {false, {}, {}};
                }
            }
            if (!((plus == 1 && minus == 1) || (plus == 0 && minus == 0))) {
                return {false, {}, {}};
            }
            if (start == -1) {
                for (int v = 0; v < n; ++v) {
                    if (outdeg[v] > 0) {
                        start = v;
                        break;
                    }
                }
            }
        } else {
            int odd = 0;
            for (int v = 0; v < n; ++v) {
                if (deg[v] & 1) {
                    start = v;
                    ++odd;
                }
            }
            if (!(odd == 0 || odd == 2)) return {false, {}, {}};
            if (start == -1) {
                for (int v = 0; v < n; ++v) {
                    if (deg[v] > 0) {
                        start = v;
                        break;
                    }
                }
            }
        }

        vector<int> ptr(n), used(m);
        vector<int> st_v{start}, st_e{-1};
        vector<int> vs, es;
        while (!st_v.empty()) {
            int v = st_v.back();
            while (ptr[v] < (int)g[v].size() && used[g[v][ptr[v]].second]) ++ptr[v];
            if (ptr[v] == (int)g[v].size()) {
                vs.push_back(v);
                st_v.pop_back();
                int id = st_e.back();
                st_e.pop_back();
                if (id != -1) es.push_back(id);
                continue;
            }
            auto [to, id] = g[v][ptr[v]++];
            if (used[id]) continue;
            used[id] = 1;
            st_v.push_back(to);
            st_e.push_back(id);
        }

        if ((int)es.size() != m) return {false, {}, {}};
        reverse(vs.begin(), vs.end());
        reverse(es.begin(), es.end());
        return {true, vs, es};
    }
};

/**
 * @brief オイラー路(Eulerian Trail)
 */
