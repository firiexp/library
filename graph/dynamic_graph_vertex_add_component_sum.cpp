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
    vector<long long> initial;

    DynamicGraphVertexAddComponentSum(const vector<long long> &a, int q)
        : n((int)a.size()), q(q), initial(a) {
        sz = 1;
        while (sz < q) sz <<= 1;
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

    template<class F>
    void for_segment(int l, int r, const F &f) const {
        for (l += sz, r += sz; l < r; l >>= 1, r >>= 1) {
            if (l & 1) f(l++);
            if (r & 1) f(--r);
        }
    }

    vector<long long> solve() {
        struct Interval {
            int l, r, u, v;
        };
        vector<Interval> intervals;
        int edge_count = 0;
        for (auto query : queries) edge_count += query.type == 0;
        intervals.reserve(edge_count);
        map<pair<int, int>, int> appear;
        for (int t = 0; t < q; ++t) {
            auto query = queries[t];
            if (query.type == 0) {
                appear[minmax(query.u, query.v)] = t;
            } else if (query.type == 1) {
                auto e = minmax(query.u, query.v);
                intervals.push_back({appear[e], t, e.first, e.second});
                appear.erase(e);
            }
        }
        for (auto &&[e, l] : appear) intervals.push_back({l, q, e.first, e.second});

        vector<size_t> edge_offset(2 * sz + 1), add_offset(2 * sz + 1);
        for (auto e : intervals)
            for_segment(e.l, e.r, [&](int k) { ++edge_offset[k + 1]; });
        for (int t = 0; t < q; ++t)
            if (queries[t].type == 2)
                for_segment(t, q, [&](int k) { ++add_offset[k + 1]; });
        for (int k = 0; k < 2 * sz; ++k) {
            edge_offset[k + 1] += edge_offset[k];
            add_offset[k + 1] += add_offset[k];
        }
        vector<EdgeEvent> seg_edges(edge_offset.back());
        vector<AddEvent> seg_adds(add_offset.back());
        auto cursor = edge_offset;
        for (auto e : intervals)
            for_segment(e.l, e.r, [&](int k) { seg_edges[cursor[k]++] = {e.u, e.v}; });
        cursor = add_offset;
        for (int t = 0; t < q; ++t) {
            auto query = queries[t];
            if (query.type == 2)
                for_segment(t, q, [&](int k) { seg_adds[cursor[k]++] = {query.u, query.x}; });
        }

        RollbackUnionFindComponentSum uf(n, initial);
        vector<long long> ans;
        ans.reserve(q);
        auto dfs = [&](auto &&self, int k) -> void {
            int snap = uf.snapshot();
            for (size_t i = edge_offset[k]; i < edge_offset[k + 1]; ++i)
                uf.unite(seg_edges[i].u, seg_edges[i].v);
            for (size_t i = add_offset[k]; i < add_offset[k + 1]; ++i)
                uf.add_value(seg_adds[i].v, seg_adds[i].x);
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
 * @brief Dynamic Graph Vertex Add Component Sum
 */
