#ifndef FIRIEXP_LIBRARY_GRAPH_BICONNECTED_COMPONENTS_CPP
#define FIRIEXP_LIBRARY_GRAPH_BICONNECTED_COMPONENTS_CPP

class BiconnectedComponents {
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
    vector<int> st;

    struct Frame {
        int v, parent_edge, next;
    };

    int other(int id, int v) const {
        return edges[id].first ^ edges[id].second ^ v;
    }

    void dfs(int i, const CSR &G, int &pos, vector<Frame> &stack){
        ord[i] = low[i] = pos++;
        stack.push_back({i, -1, G.start[i]});
        while (!stack.empty()) {
            auto &frame = stack.back();
            int v = frame.v;
            if (frame.next == G.start[v + 1]) {
                int pe = frame.parent_edge, p = par[v];
                stack.pop_back();
                if (p == -1) continue;
                low[p] = min(low[p], low[v]);
                if (ord[p] <= low[v]) {
                    bcc_edges.emplace_back();
                    while (true) {
                        int k = st.back();
                        st.pop_back();
                        bcc_edges.back().emplace_back(min(edges[k].first, edges[k].second), max(edges[k].first, edges[k].second));
                        if (k == pe) break;
                    }
                }
                continue;
            }
            int id = G.elist[frame.next++];
            if (id == frame.parent_edge) continue;
            int j = other(id, v);
            if(ord[j] < ord[v]) st.emplace_back(id);
            if(~ord[j]){
                low[v] = min(low[v], ord[j]);
                continue;
            }
            par[j] = v;
            ord[j] = low[j] = pos++;
            stack.push_back({j, id, G.start[j]});
        }
    }
public:
    vector<int> ord, low, par;
    vector<pair<int, int>> edges;
    vector<vector<pair<int, int>>> bcc_edges;
    vector<vector<int>> bcc_vertices;
    explicit BiconnectedComponents(int n): n(n), ord(n, -1), low(n), par(n, -1){}

    void add_edge(int u, int v){
        if(u == v) return;
        edges.emplace_back(u, v);
    }

    int build(){
        CSR G(n, edges);
        int pos = 0;
        fill(ord.begin(), ord.end(), -1);
        fill(par.begin(), par.end(), -1);
        bcc_edges.clear();
        bcc_vertices.clear();
        st.clear();
        vector<Frame> stack;
        for (int i = 0; i < n; ++i) {
            if(ord[i] < 0) dfs(i, G, pos, stack);
        }
        vector<int> seen(n, -1);
        bcc_vertices.reserve(bcc_edges.size());
        for (int i = 0; i < (int)bcc_edges.size(); ++i) {
            vector<int> now;
            for (auto &&e : bcc_edges[i]) {
                if(seen[e.first] != i){
                    seen[e.first] = i;
                    now.emplace_back(e.first);
                }
                if(seen[e.second] != i){
                    seen[e.second] = i;
                    now.emplace_back(e.second);
                }
            }
            bcc_vertices.emplace_back(std::move(now));
        }
        for (int i = 0; i < n; ++i) {
            if(G.start[i] == G.start[i + 1]){
                bcc_edges.emplace_back();
                bcc_vertices.push_back({i});
            }
        }
        return bcc_vertices.size();
    }
};

/**
 * @brief 二重連結成分分解(Biconnected Components)
 */

#endif
