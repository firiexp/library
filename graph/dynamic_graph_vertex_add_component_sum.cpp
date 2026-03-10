#include <algorithm>
#include <map>
#include <utility>
#include <vector>
using namespace std;

struct RollbackUnionFindComponentSum {
    struct History {
        int child, parent;
        int parent_size, child_size;
        long long parent_sum, child_sum;
    };

    vector<int> parent_or_size;
    vector<long long> comp_sum;
    vector<History> history;

    explicit RollbackUnionFindComponentSum(int n, const vector<long long> &a)
        : parent_or_size(n, -1), comp_sum(a) {}

    int root(int v) const {
        while (parent_or_size[v] >= 0) v = parent_or_size[v];
        return v;
    }

    int snapshot() const {
        return (int)history.size();
    }

    void rollback(int snap) {
        while ((int)history.size() > snap) {
            auto h = history.back();
            history.pop_back();
            if (h.parent == -1) continue;
            parent_or_size[h.parent] = h.parent_size;
            parent_or_size[h.child] = h.child_size;
            comp_sum[h.parent] = h.parent_sum;
            comp_sum[h.child] = h.child_sum;
        }
    }

    void unite(int a, int b) {
        a = root(a), b = root(b);
        if (a == b) {
            history.push_back({-1, -1, 0, 0, 0, 0});
            return;
        }
        if (parent_or_size[a] > parent_or_size[b]) swap(a, b);
        history.push_back({b, a, parent_or_size[a], parent_or_size[b], comp_sum[a], comp_sum[b]});
        parent_or_size[a] += parent_or_size[b];
        parent_or_size[b] = a;
        comp_sum[a] += comp_sum[b];
    }

    void add_value(int v, long long x) {
        int r = root(v);
        history.push_back({r, r, parent_or_size[r], parent_or_size[r], comp_sum[r], comp_sum[r]});
        comp_sum[r] += x;
    }

    long long get_sum(int v) const {
        return comp_sum[root(v)];
    }
};

struct DynamicGraphVertexAddComponentSum {
    struct Query {
        int type, u, v;
        long long x;
    };
    struct EdgeEvent {
        int u, v;
    };
    struct AddEvent {
        int v;
        long long x;
    };

    int n, q, sz;
    vector<Query> queries;
    vector<vector<EdgeEvent>> seg_edges;
    vector<vector<AddEvent>> seg_adds;
    vector<long long> initial;

    DynamicGraphVertexAddComponentSum(const vector<long long> &a, int q)
        : n((int)a.size()), q(q), initial(a) {
        sz = 1;
        while (sz < q) sz <<= 1;
        seg_edges.resize(2 * sz);
        seg_adds.resize(2 * sz);
        queries.reserve(q);
    }

    void add_edge(int u, int v) {
        queries.push_back({0, u, v, 0});
    }

    void erase_edge(int u, int v) {
        queries.push_back({1, u, v, 0});
    }

    void add_vertex(int v, long long x) {
        queries.push_back({2, v, 0, x});
    }

    void add_component_query(int v) {
        queries.push_back({3, v, 0, 0});
    }

    template<class T>
    void add_segment(vector<vector<T>> &seg, int l, int r, const T &event) {
        for (l += sz, r += sz; l < r; l >>= 1, r >>= 1) {
            if (l & 1) seg[l++].push_back(event);
            if (r & 1) seg[--r].push_back(event);
        }
    }

    vector<long long> solve() {
        map<pair<int, int>, int> appear;
        for (int t = 0; t < q; ++t) {
            auto query = queries[t];
            if (query.type == 0) {
                appear[minmax(query.u, query.v)] = t;
            } else if (query.type == 1) {
                auto e = minmax(query.u, query.v);
                add_segment(seg_edges, appear[e], t, {e.first, e.second});
                appear.erase(e);
            } else if (query.type == 2) {
                add_segment(seg_adds, t, q, {query.u, query.x});
            }
        }
        for (auto &&[e, l] : appear) add_segment(seg_edges, l, q, {e.first, e.second});

        RollbackUnionFindComponentSum uf(n, initial);
        vector<long long> ans;
        ans.reserve(q);
        auto dfs = [&](auto &&self, int k) -> void {
            int snap = uf.snapshot();
            for (auto &&e : seg_edges[k]) uf.unite(e.u, e.v);
            for (auto &&a : seg_adds[k]) uf.add_value(a.v, a.x);
            if (k < sz) {
                self(self, k << 1);
                self(self, k << 1 | 1);
            } else {
                int t = k - sz;
                if (t < q && queries[t].type == 3) ans.push_back(uf.get_sum(queries[t].u));
            }
            uf.rollback(snap);
        };
        dfs(dfs, 1);
        return ans;
    }
};

/**
 * @brief 動的グラフ連結成分和(Dynamic Graph Vertex Add Component Sum)
 */
