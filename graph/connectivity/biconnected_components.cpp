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
            for (auto [u, v] : edges) {
                elist[counter[u]++] = v;
                elist[counter[v]++] = u;
            }
        }
    };

    int n = 0;

    struct Frame {
        int v, skip_parent, next, edge_begin;
    };

    template<class It>
    void add_vertices(It first, It last, vector<int> &seen) {
        auto [u, v] = *first++;
        int component = bcc_vertices.size();
        bcc_vertices.push_back({u, v});
        if (first == last) return;
        auto &vertices = bcc_vertices.back();
        seen[u] = seen[v] = component;
        for (; first != last; ++first) {
            auto [a, b] = *first;
            if (seen[a] != component) {
                seen[a] = component;
                vertices.push_back(a);
            }
            if (seen[b] != component) {
                seen[b] = component;
                vertices.push_back(b);
            }
        }
    }

    void decompose(const CSR &g, bool build_edges) {
        int pos = 0;
        vector<int> seen(build_edges ? 0 : n, -1);
        vector<Frame> stack;
        vector<pair<int, int>> pending;
        for (int root = 0; root < n; ++root) {
            if (ord[root] != -1) continue;
            ord[root] = low[root] = pos++;
            stack.push_back({root, -1, g.start[root], 0});
            while (!stack.empty()) {
                auto &frame = stack.back();
                int v = frame.v;
                if (frame.next == g.start[v + 1]) {
                    int p = par[v], first = frame.edge_begin;
                    stack.pop_back();
                    if (p == -1) continue;
                    low[p] = min(low[p], low[v]);
                    if (ord[p] <= low[v]) {
                        auto begin = pending.rbegin(), end = pending.rend() - first;
                        if (build_edges) bcc_edges.emplace_back(begin, end);
                        else add_vertices(begin, end, seen);
                        pending.resize(first);
                    }
                    continue;
                }
                int u = g.elist[frame.next++];
                if (u == frame.skip_parent) {
                    frame.skip_parent = -1;
                    continue;
                }
                if (ord[u] < ord[v]) pending.push_back(minmax(u, v));
                if (ord[u] != -1) {
                    low[v] = min(low[v], ord[u]);
                    continue;
                }
                par[u] = v;
                ord[u] = low[u] = pos++;
                stack.push_back({u, v, g.start[u], int(pending.size()) - 1});
            }
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

    int build(bool build_edges = true) {
        CSR G(n, edges);
        fill(ord.begin(), ord.end(), -1);
        fill(par.begin(), par.end(), -1);
        bcc_edges.clear();
        bcc_vertices.clear();
        decompose(G, build_edges);
        if (build_edges) {
            vector<int> seen(n, -1);
            bcc_vertices.reserve(bcc_edges.size());
            for (const auto &block : bcc_edges) add_vertices(block.begin(), block.end(), seen);
        }
        for (int i = 0; i < n; ++i) {
            if(G.start[i] == G.start[i + 1]){
                if (build_edges) bcc_edges.emplace_back();
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
