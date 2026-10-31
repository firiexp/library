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
        int ss = n, tt = n + 1;
        Dinic<T, true> mf(n + 2);
        vector<T> b(n, 0);
        vector<int> edge_ids;
        edge_ids.reserve(edges.size());
        for(auto &&e : edges) {
            edge_ids.push_back(mf.add_edge(e.from, e.to, e.upper - e.lower));
            b[e.from] -= e.lower;
            b[e.to] += e.lower;
        }

        int ts_index = mf.G[t].size();
        int ts = mf.add_edge(t, s, INF<T>);
        T req = 0;
        vector<int> super_edges;
        for(int v = 0; v < n; ++v) {
            if(b[v] > 0) {
                req += b[v];
                super_edges.push_back(mf.add_edge(ss, v, b[v]));
            } else if(b[v] < 0) {
                mf.add_edge(v, tt, -b[v]);
            }
        }

        if(mf.flow(ss, tt) != req) return {false, 0, {}};

        for(int id : super_edges) {
            auto e = mf.get_edge(id);
            if(e.flow != e.capacity) return {false, 0, {}};
        }

        T base = mf.get_edge(ts).flow;
        auto &aux = mf.G[t][ts_index];
        mf.G[aux.to][aux.rev].cap = 0;
        aux.cap = 0;

        T add = mf.flow(s, t);
        Result result{true, base + add, {}};
        result.edge_flow.reserve(edges.size());
        for(size_t i = 0; i < edges.size(); ++i) {
            result.edge_flow.push_back(edges[i].lower + mf.get_edge(edge_ids[i]).flow);
        }
        return result;
    }
};

/**
 * @brief 下限制約付きs-t最大流 (Max Flow with Lower Bounds)
 */
