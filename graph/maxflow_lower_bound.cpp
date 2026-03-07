template<class T>
class MaxFlowLowerBound {
    struct Dinic {
        struct edge {
            int to{};
            T cap{};
            int rev{};
            edge() = default;
            edge(int to, T cap, int rev) : to(to), cap(cap), rev(rev) {}
        };

        vector<vector<edge>> G;
        vector<int> level, iter;

        Dinic() = default;
        explicit Dinic(int n) : G(n), level(n), iter(n) {}

        pair<int, int> add_edge(int from, int to, T cap) {
            int fi = (int)G[from].size();
            int ti = (int)G[to].size();
            G[from].emplace_back(to, cap, ti);
            G[to].emplace_back(from, 0, fi);
            return {from, fi};
        }

        void bfs(int s) {
            fill(level.begin(), level.end(), -1);
            queue<int> q;
            level[s] = 0;
            q.emplace(s);
            while(!q.empty()) {
                int v = q.front();
                q.pop();
                for(auto &&e : G[v]) {
                    if(e.cap > 0 && level[e.to] < 0) {
                        level[e.to] = level[v] + 1;
                        q.emplace(e.to);
                    }
                }
            }
        }

        T dfs(int v, int t, T f) {
            if(v == t) return f;
            for(int &i = iter[v]; i < (int)G[v].size(); ++i) {
                edge &e = G[v][i];
                if(e.cap > 0 && level[v] < level[e.to]) {
                    T d = dfs(e.to, t, min(f, e.cap));
                    if(d == 0) continue;
                    e.cap -= d;
                    G[e.to][e.rev].cap += d;
                    return d;
                }
            }
            return 0;
        }

        T flow(int s, int t, T lim = INF<T>) {
            T ret = 0;
            while(lim > 0) {
                bfs(s);
                if(level[t] < 0) break;
                fill(iter.begin(), iter.end(), 0);
                while(lim > 0) {
                    T f = dfs(s, t, lim);
                    if(f == 0) break;
                    ret += f;
                    lim -= f;
                }
            }
            return ret;
        }
    };

    struct raw_edge {
        int from{}, to{};
        T lower{}, upper{};
    };

public:
    int n;
    vector<raw_edge> edges;
    MaxFlowLowerBound() = default;
    explicit MaxFlowLowerBound(int n) : n(n) {}

    void add_edge(int from, int to, T lower, T upper) {
        edges.push_back({from, to, lower, upper});
    }

    pair<bool, T> max_flow(int s, int t) {
        int ss = n, tt = n + 1;
        Dinic mf(n + 2);
        vector<T> b(n, 0);

        for(auto &&e : edges) {
            mf.add_edge(e.from, e.to, e.upper - e.lower);
            b[e.from] -= e.lower;
            b[e.to] += e.lower;
        }

        auto ts = mf.add_edge(t, s, INF<T>);
        T req = 0;
        vector<pair<int, int>> super_edges;
        for(int v = 0; v < n; ++v) {
            if(b[v] > 0) {
                req += b[v];
                super_edges.emplace_back(mf.add_edge(ss, v, b[v]));
            } else if(b[v] < 0) {
                mf.add_edge(v, tt, -b[v]);
            }
        }

        if(mf.flow(ss, tt) != req) return {false, 0};

        for(auto &&id : super_edges) {
            if(mf.G[id.first][id.second].cap != 0) return {false, 0};
        }

        int to = mf.G[ts.first][ts.second].to;
        int rev = mf.G[ts.first][ts.second].rev;
        T base = mf.G[to][rev].cap;
        mf.G[ts.first][ts.second].cap = 0;
        mf.G[to][rev].cap = 0;

        T add = mf.flow(s, t);
        return {true, base + add};
    }
};

/**
 * @brief 下限制約付き s-t 最大流
 * @docs _md/maxflow_lower_bound.md
 */
