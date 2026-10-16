#ifndef FIRIEXP_LIBRARY_GRAPH_MINIMUM_STEINER_TREE_CPP
#define FIRIEXP_LIBRARY_GRAPH_MINIMUM_STEINER_TREE_CPP

template <class T>
class MinimumSteinerTree {
    struct Edge { int u, v; T cost; };

    int n;
    vector<Edge> edges;
    vector<vector<int>> graph;
    vector<vector<T>> dp;
    vector<vector<int>> trace;

public:
    explicit MinimumSteinerTree(int n) : n(n), graph(n) {
        assert(n > 0);
    }

    int add_edge(int u, int v, T weight) {
        assert(0 <= u && u < n && 0 <= v && v < n && weight >= 0);
        int id = (int)edges.size();
        edges.push_back({u, v, weight});
        graph[u].push_back(id);
        graph[v].push_back(id);
        return id;
    }

    void build(const vector<int> &terminals) {
        int k = (int)terminals.size();
        vector<char> used(n);
        for (int v : terminals) {
            assert(0 <= v && v < n && !used[v]);
            used[v] = true;
        }
        int states = 1 << k;
        dp.assign(states, vector<T>(n, INF<T>));
        trace.assign(states, vector<int>(n, -1));
        for (int i = 0; i < k; ++i) dp[1 << i][terminals[i]] = 0;
        for (int mask = 1; mask < states; ++mask) {
            auto &dist = dp[mask];
            for (int sub = (mask - 1) & mask; sub; sub = (sub - 1) & mask) {
                int other = mask ^ sub;
                if (sub < other) continue;
                for (int v = 0; v < n; ++v) {
                    if (dp[sub][v] >= INF<T> - dp[other][v]) continue;
                    T next = dp[sub][v] + dp[other][v];
                    if (next >= dist[v]) continue;
                    dist[v] = next;
                    trace[mask][v] = sub;
                }
            }
            priority_queue<pair<T, int>, vector<pair<T, int>>, greater<>> queue;
            for (int v = 0; v < n; ++v) {
                if (dist[v] != INF<T>) queue.emplace(dist[v], v);
            }
            while (!queue.empty()) {
                auto [value, v] = queue.top();
                queue.pop();
                if (value != dist[v]) continue;
                for (int id : graph[v]) {
                    const auto &e = edges[id];
                    int u = e.u ^ e.v ^ v;
                    if (e.cost >= INF<T> - value) continue;
                    T next = value + e.cost;
                    if (next >= dist[u]) continue;
                    dist[u] = next;
                    trace[mask][u] = -id - 2;
                    queue.emplace(next, u);
                }
            }
        }
    }

    T cost(int v) const {
        return dp.back()[v];
    }

    vector<int> restore(int v) const {
        if (cost(v) == INF<T>) return {};
        vector<int> result, parent(n, -1);
        auto root = [&](auto &&self, int u) -> int {
            return parent[u] < 0 ? u : parent[u] = self(self, parent[u]);
        };
        vector<pair<int, int>> pending{ { (int)dp.size() - 1, v } };
        while (!pending.empty()) {
            auto [mask, u] = pending.back();
            pending.pop_back();
            int step = trace[mask][u];
            if (step == -1) continue;
            if (step >= 0) {
                pending.emplace_back(step, u);
                pending.emplace_back(mask ^ step, u);
            } else {
                int id = -step - 2;
                const auto &e = edges[id];
                pending.emplace_back(mask, e.u ^ e.v ^ u);
                int a = root(root, e.u), b = root(root, e.v);
                if (a == b) continue;
                if (parent[a] > parent[b]) swap(a, b);
                parent[a] += parent[b];
                parent[b] = a;
                result.push_back(id);
            }
        }
        return result;
    }
};

#endif

/**
 * @brief 最小シュタイナー木
 */
