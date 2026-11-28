#ifndef FIRIEXP_LIBRARY_GRAPH_SCC_CPP
#define FIRIEXP_LIBRARY_GRAPH_SCC_CPP

class SCC {
    struct CSR {
        vector<int> start, elist;

        CSR() = default;

        CSR(int n, const vector<pair<int, int>> &edges, bool rev) : start(n + 1), elist(edges.size()) {
            for (auto &&[a, b] : edges) {
                ++start[(rev ? b : a) + 1];
            }
            for (int i = 0; i < n; ++i) start[i + 1] += start[i];
            auto counter = start;
            for (auto &&[a, b] : edges) {
                int from = rev ? b : a;
                int to = rev ? a : b;
                elist[counter[from]++] = to;
            }
        }
    };

    int n = 0;
    vector<pair<int, int>> edges;

public:
    vector<vector<int>> G_out;
    vector<int> vs, used, cmp, sz;
    SCC() = default;
    explicit SCC(int n) : n(n), used(n), cmp(n), sz(n) {}

    void add_edge(int a, int b){
        edges.emplace_back(a, b);
    }

    int build(bool build_dag = true) {
        CSR G(n, edges, false), G_r(n, edges, true);
        vs.clear();
        vs.reserve(n);
        fill(used.begin(), used.end(), 0);
        vector<int> stack, cursor = G.start;
        for (int start = 0; start < n; ++start) {
            if (used[start]) continue;
            used[start] = 1;
            stack.push_back(start);
            while (!stack.empty()) {
                int v = stack.back();
                if (cursor[v] == G.start[v + 1]) {
                    vs.push_back(v);
                    stack.pop_back();
                    continue;
                }
                int u = G.elist[cursor[v]++];
                if (used[u]) continue;
                used[u] = 1;
                stack.push_back(u);
            }
        }
        fill(used.begin(), used.end(), 0);
        sz.resize(n);
        fill(sz.begin(), sz.end(), 0);
        int k = 0;
        for (int i = n - 1; i >= 0; --i) {
            int start = vs[i];
            if (used[start]) continue;
            used[start] = 1;
            stack.push_back(start);
            while (!stack.empty()) {
                int v = stack.back();
                stack.pop_back();
                cmp[v] = k;
                ++sz[k];
                for (int ei = G_r.start[v]; ei < G_r.start[v + 1]; ++ei) {
                    int u = G_r.elist[ei];
                    if (used[u]) continue;
                    used[u] = 1;
                    stack.push_back(u);
                }
            }
            ++k;
        }
        G_out.assign(build_dag ? k : 0, {});
        sz.resize(k);
        if (!build_dag || k <= 1) return k;
        vector<int> head(k, -1), next(n), seen(k, -1);
        for (int v = 0; v < n; ++v) {
            next[v] = head[cmp[v]];
            head[cmp[v]] = v;
        }
        for (int to = 0; to < k; ++to) {
            for (int v = head[to]; v != -1; v = next[v]) {
                for (int ei = G_r.start[v]; ei < G_r.start[v + 1]; ++ei) {
                    int from = cmp[G_r.elist[ei]];
                    if (from == to || seen[from] == to) continue;
                    seen[from] = to;
                    G_out[from].push_back(to);
                }
            }
        }
        return k;
    }

    int operator[](int k) const { return cmp[k]; }

    vector<vector<int>> groups() const {
        vector<vector<int>> result(sz.size());
        for (int c = 0; c < int(sz.size()); ++c) result[c].reserve(sz[c]);
        for (int v = 0; v < n; ++v) result[cmp[v]].push_back(v);
        return result;
    }
};

#endif

/**
 * @brief 強連結成分分解(SCC)
 */
