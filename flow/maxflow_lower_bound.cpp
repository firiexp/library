#include "dinic.cpp"

template<class T>
class MaxFlowLowerBound {

    struct raw_edge {
        int from{}, to{};
        T lower{}, upper{};
    };

public:
    struct Result {
        bool exists;
        T value;
        vector<T> edge_flow;
    };

    int n;
    vector<raw_edge> edges;
    MaxFlowLowerBound() = default;
    explicit MaxFlowLowerBound(int n) : n(n) {}

    void add_edge(int from, int to, T lower, T upper) {
        edges.push_back({from, to, lower, upper});
    }

    pair<bool, T> max_flow(int s, int t) {
        auto result = max_flow_with_edges(s, t);
        return {result.exists, result.value};
    }

    Result max_flow_with_edges(int s, int t) {
        return solve(s, t, false);
    }

    Result min_flow_with_edges(int s, int t) {
        return solve(s, t, true);
    }

private:
    Result solve(int s, int t, bool minimize) {
        int ss = n, tt = n + 1;
        Dinic<T, true> mf(n + 2);
        vector<T> b(n, 0);
        for(auto &&e : edges) {
            mf.add_edge(e.from, e.to, e.upper - e.lower);
            b[e.from] -= e.lower;
            b[e.to] += e.lower;
        }

        int ts = mf.add_edge(t, s, INF<T>);
        T req = 0;
        int last_auxiliary = ts;
        for(int v = 0; v < n; ++v) {
            if(b[v] > 0) {
                req += b[v];
                last_auxiliary = mf.add_edge(ss, v, b[v]);
            } else if(b[v] < 0) {
                last_auxiliary = mf.add_edge(v, tt, -b[v]);
            }
        }

        if(mf.flow(ss, tt) != req) return {false, 0, {}};

        T base = mf.get_edge(ts).flow;
        for(int id = ts; id <= last_auxiliary; ++id) mf.change_edge(id, 0, 0);

        T value = minimize ? base - mf.flow(t, s, base) : base + mf.flow(s, t);
        Result result{true, value, {}};
        result.edge_flow.reserve(edges.size());
        for(size_t i = 0; i < edges.size(); ++i) {
            result.edge_flow.push_back(edges[i].lower + mf.get_edge(i).flow);
        }
        return result;
    }
};

/**
 * @brief 下限制約付きs-t流
 */
