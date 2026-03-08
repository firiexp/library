template<class Flow, class Cost>
struct MinimumCostBFlow {
    using Sum = __int128_t;
    struct Edge {
        int from, to, rev;
        Flow flow, cap;
        Cost cost;

        Flow residual_cap() const {
            return cap - flow;
        }
    };

    struct EdgeRef {
        int from, idx;
    };

    int n;
    vector<vector<Edge>> g;
    vector<Flow> b;
    vector<EdgeRef> edges;
    vector<Cost> potential;

    explicit MinimumCostBFlow(int n) : n(n), g(n), b(n, 0), potential(n, 0) {}

    void add_supply(int v, Flow x) {
        b[v] += x;
    }

    void add_demand(int v, Flow x) {
        b[v] -= x;
    }

    int add_edge(int from, int to, Flow lower, Flow upper, Cost cost) {
        assert(lower <= upper);
        int idx = (int)g[from].size();
        int rev = from == to ? idx + 1 : (int)g[to].size();
        g[from].push_back({from, to, rev, 0, upper, cost});
        g[to].push_back({to, from, idx, 0, -lower, -cost});
        edges.push_back({from, idx});
        return (int)edges.size() - 1;
    }

    Edge& rev_edge(const Edge& e) {
        return g[e.to][e.rev];
    }

    const Edge& get_edge(int i) const {
        return g[edges[i].from][edges[i].idx];
    }

    vector<Flow> get_flows() const {
        vector<Flow> ret(edges.size());
        for (int i = 0; i < (int)edges.size(); ++i) ret[i] = get_edge(i).flow;
        return ret;
    }

    vector<Cost> get_potential() const {
        vector<Cost> ret(n, 0);
        for (int iter = 0; iter < n; ++iter) {
            bool updated = false;
            for (int v = 0; v < n; ++v) {
                for (auto&& e : g[v]) {
                    if(e.residual_cap() <= 0) continue;
                    if(ret[e.to] > ret[e.from] + e.cost) {
                        ret[e.to] = ret[e.from] + e.cost;
                        updated = true;
                    }
                }
            }
            if(!updated) break;
        }
        return ret;
    }

    pair<bool, Sum> solve() {
        const Cost unreachable = numeric_limits<Cost>::max();
        vector<Cost> dist(n);
        vector<Edge*> parent(n);
        vector<int> excess, deficit;
        priority_queue<pair<Cost, int>, vector<pair<Cost, int>>, greater<pair<Cost, int>>> pq;
        Cost farthest = 0;

        auto push = [&](Edge& e, Flow amount) {
            e.flow += amount;
            rev_edge(e).flow -= amount;
        };
        auto residual_cost = [&](const Edge& e) {
            return e.cost + potential[e.from] - potential[e.to];
        };

        auto saturate_negative = [&](Flow delta) {
            excess.clear();
            deficit.clear();
            for (auto&& es : g) {
                for (auto&& e : es) {
                    Flow rcap = e.residual_cap();
                    if(rcap < delta) continue;
                    if(residual_cost(e) < 0) {
                        push(e, rcap);
                        b[e.from] -= rcap;
                        b[e.to] += rcap;
                    }
                }
            }
            for (int v = 0; v < n; ++v) {
                if(b[v] > 0) excess.push_back(v);
                if(b[v] < 0) deficit.push_back(v);
            }
        };

        auto dual = [&](Flow delta) {
            fill(dist.begin(), dist.end(), unreachable);
            fill(parent.begin(), parent.end(), nullptr);

            excess.erase(remove_if(excess.begin(), excess.end(), [&](int v) {
                return b[v] < delta;
            }), excess.end());
            deficit.erase(remove_if(deficit.begin(), deficit.end(), [&](int v) {
                return b[v] > -delta;
            }), deficit.end());

            while(!pq.empty()) pq.pop();
            for (int v : excess) {
                dist[v] = 0;
                pq.emplace(0, v);
            }

            farthest = 0;
            int reached = 0;
            while(!pq.empty()) {
                auto [d, v] = pq.top();
                pq.pop();
                if(dist[v] != d) continue;
                farthest = d;
                if(b[v] <= -delta) ++reached;
                if(reached >= (int)deficit.size()) break;
                for (auto&& e : g[v]) {
                    if(e.residual_cap() < delta) continue;
                    Cost nd = d + residual_cost(e);
                    if(nd >= dist[e.to]) continue;
                    dist[e.to] = nd;
                    parent[e.to] = &e;
                    pq.emplace(nd, e.to);
                }
            }

            for (int v = 0; v < n; ++v) {
                potential[v] += min(dist[v], farthest);
            }
            return reached > 0;
        };

        auto primal = [&](Flow delta) {
            for (int t : deficit) {
                if(dist[t] > farthest) continue;
                Flow f = -b[t];
                int v = t;
                while(parent[v] != nullptr && f >= delta) {
                    f = min(f, parent[v]->residual_cap());
                    v = parent[v]->from;
                }
                f = min(f, b[v]);
                if(f < delta) continue;
                v = t;
                while(parent[v] != nullptr) {
                    Edge& e = *parent[v];
                    push(e, f);
                    int u = e.from;
                    parent[v] = nullptr;
                    v = u;
                }
                b[t] += f;
                b[v] -= f;
            }
        };

        for (auto&& es : g) {
            for (auto&& e : es) {
                Flow rcap = e.residual_cap();
                if(rcap < 0) {
                    push(e, rcap);
                    b[e.from] -= rcap;
                    b[e.to] += rcap;
                }
            }
        }

        Flow max_cap = 1;
        for (auto&& es : g) {
            for (auto&& e : es) {
                max_cap = max(max_cap, e.residual_cap());
            }
        }
        Flow delta = 1;
        while(delta <= max_cap / 2) delta <<= 1;
        for (delta >>= 1; delta > 0; delta >>= 1) {
            saturate_negative(delta);
            while(dual(delta)) primal(delta);
        }

        Sum value = 0;
        bool ok = true;
        for (int v = 0; v < n; ++v) {
            if(b[v] != 0) ok = false;
        }
        for (int i = 0; i < (int)edges.size(); ++i) {
            auto&& e = get_edge(i);
            value += (Sum)e.flow * (Sum)e.cost;
        }
        return {ok, value};
    }
};

/**
 * @brief 最小費用 b-flow
 * @docs _md/minimum_cost_b_flow.md
 */
