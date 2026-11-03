#ifndef FIRIEXP_LIBRARY_GRAPH_TWO_EDGE_CONNECTED_COMPONENTS_CPP
#define FIRIEXP_LIBRARY_GRAPH_TWO_EDGE_CONNECTED_COMPONENTS_CPP

class TwoEdgeConnectedComponents {
    struct CSR {
        vector<int> start, elist;

        CSR() = default;

        CSR(int n, const vector<pair<int, int>> &edges) : start(n + 1), elist(edges.size() * 2) {
            for (auto &&[u, v] : edges) {
                ++start[u + 1];
                ++start[v + 1];
            }
            for (int i = 0; i < n; ++i) start[i + 1] += start[i];
            auto counter = start;
            for (int id = 0; id < (int)edges.size(); ++id) {
                auto &&[u, v] = edges[id];
                elist[counter[u]++] = id;
                elist[counter[v]++] = id;
            }
        }
    };

    int n = 0;

    int other(int id, int v) const {
        return edges[id].first ^ edges[id].second ^ v;
    }

public:
    vector<int> ord, low, par, bridge, size;
    vector<pair<int, int>> edges;
    vector<vector<int>> out;
    explicit TwoEdgeConnectedComponents(int n): n(n), ord(n, -1), low(n), par(n, -1), bridge(n, -1), size(n, 1){}

    inline bool is_bridge(int i, int j){
        if(ord[i] > ord[j]) swap(i, j);
        return ord[i] < low[j];
    }

    bool is_bridge_edge(int id) const {
        auto [u, v] = edges[id];
        if(ord[u] > ord[v]) swap(u, v);
        return ord[u] < low[v];
    }

    void add_edge(int u, int v){
        if(u == v) return;
        edges.emplace_back(u, v);
    }

    int build(){
        CSR G(n, edges);
        fill(ord.begin(), ord.end(), -1);
        fill(par.begin(), par.end(), -1);
        fill(size.begin(), size.end(), 1);
        out.clear();
        struct Frame {
            int vertex, parent_edge, next;
        };
        vector<Frame> stack;
        vector<int> order;
        stack.reserve(n);
        order.reserve(n);
        for (int root = 0; root < n; ++root) {
            if (ord[root] >= 0) continue;
            ord[root] = low[root] = order.size();
            order.push_back(root);
            stack.push_back({root, -1, G.start[root]});
            while (!stack.empty()) {
                auto &frame = stack.back();
                int v = frame.vertex;
                if (frame.next == G.start[v + 1]) {
                    stack.pop_back();
                    if (par[v] >= 0) {
                        size[par[v]] += size[v];
                        low[par[v]] = min(low[par[v]], low[v]);
                    }
                    continue;
                }
                int id = G.elist[frame.next++];
                if (id == frame.parent_edge) continue;
                int u = other(id, v);
                if (ord[u] >= 0) {
                    low[v] = min(low[v], ord[u]);
                    continue;
                }
                par[u] = v;
                ord[u] = low[u] = order.size();
                order.push_back(u);
                if (G.start[u + 1] - G.start[u] == 1) ++size[v];
                else stack.push_back({u, id, G.start[u]});
            }
        }
        for (int v : order) {
            if (par[v] < 0 || ord[par[v]] < low[v]) {
                bridge[v] = out.size();
                out.emplace_back();
            } else {
                bridge[v] = bridge[par[v]];
            }
            out[bridge[v]].push_back(v);
        }
        return out.size();
    }
};

/**
 * @brief 二辺連結成分分解(Two-Edge-Connected Components)
 */

#endif
