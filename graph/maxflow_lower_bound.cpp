#include "../flow/dinic.cpp"

template<class T>
class MaxFlowLowerBound {

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
        Dinic<T, true> mf(n + 2);
        vector<T> b(n, 0);
        auto add_edge = [&](int from, int to, T cap) {
            int idx = (int)mf.G[from].size();
            mf.add_edge(from, to, cap);
            return pair<int, int>{from, idx};
        };

        for(auto &&e : edges) {
            mf.add_edge(e.from, e.to, e.upper - e.lower);
            b[e.from] -= e.lower;
            b[e.to] += e.lower;
        }

        auto ts = add_edge(t, s, INF<T>);
        T req = 0;
        vector<pair<int, int>> super_edges;
        for(int v = 0; v < n; ++v) {
            if(b[v] > 0) {
                req += b[v];
                super_edges.emplace_back(add_edge(ss, v, b[v]));
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
 * @brief 下限制約付きs-t最大流 (Max Flow with Lower Bounds)
 */
