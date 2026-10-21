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

        vector<int> deg(n);
        for (const auto &e : edges) {
            ++deg[e.from];
            if constexpr (directed) --deg[e.to];
            else ++deg[e.to];
        }

        int start = -1, plus = 0, minus = 0;
        if constexpr (directed) {
            for (int v = 0; v < n; ++v) {
                int diff = deg[v];
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
                    if (!g[v].empty()) {
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

        vector<int> ptr(n), used;
        if constexpr (!directed) used.assign(m, 0);
        vector<int> st_v, st_e, vs, es;
        st_v.reserve((size_t)m + 1);
        st_e.reserve((size_t)m + 1);
        vs.reserve((size_t)m + 1);
        es.reserve(m);
        st_v.push_back(start);
        st_e.push_back(-1);
        while (!st_v.empty()) {
            int v = st_v.back();
            if constexpr (!directed) {
                while (ptr[v] < (int)g[v].size() && used[g[v][ptr[v]].second]) ++ptr[v];
            }
            if (ptr[v] == (int)g[v].size()) {
                vs.push_back(v);
                st_v.pop_back();
                int id = st_e.back();
                st_e.pop_back();
                if (id != -1) es.push_back(id);
                continue;
            }
            auto [to, id] = g[v][ptr[v]++];
            if constexpr (!directed) used[id] = 1;
            st_v.push_back(to);
            st_e.push_back(id);
        }

        if ((int)es.size() != m) return {false, {}, {}};
        reverse(vs.begin(), vs.end());
        reverse(es.begin(), es.end());
        return {true, move(vs), move(es)};
    }
};

/**
 * @brief オイラー路(Eulerian Trail)
 */
