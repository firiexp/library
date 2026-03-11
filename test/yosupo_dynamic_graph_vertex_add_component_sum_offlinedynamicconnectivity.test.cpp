#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum"

#include <map>
#include <utility>
#include <vector>
using namespace std;

#include "../util/fastio.cpp"
#include "../graph/offlinedynamicconnectivity.cpp"

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

int main() {
    Scanner sc;
    Printer pr;

    int n, q;
    sc.read(n, q);
    vector<long long> a(n);
    for (auto &x : a) sc.read(x);

    OfflineDynamicConnectivity dc(n, q);
    struct AddEvent {
        int v;
        long long x;
    };
    vector<vector<AddEvent>> seg_adds(2 * dc.sz);
    vector<int> type(q), query_vertex(q, -1);

    auto add_segment = [&](int l, int r, const AddEvent &event) {
        for (l += dc.sz, r += dc.sz; l < r; l >>= 1, r >>= 1) {
            if (l & 1) seg_adds[l++].push_back(event);
            if (r & 1) seg_adds[--r].push_back(event);
        }
    };

    for (int t = 0; t < q; ++t) {
        sc.read(type[t]);
        if (type[t] == 0) {
            int u, v;
            sc.read(u, v);
            dc.insert(t, u, v);
        } else if (type[t] == 1) {
            int u, v;
            sc.read(u, v);
            dc.erase(t, u, v);
        } else if (type[t] == 2) {
            int v;
            long long x;
            sc.read(v, x);
            add_segment(t, q, {v, x});
        } else {
            sc.read(query_vertex[t]);
        }
    }
    dc.build();

    RollbackUnionFindComponentSum uf(n, a);
    vector<int> snaps;
    vector<long long> ans;
    ans.reserve(q);

    dc.dfs(
        [&](int k, const vector<pair<int, int>> &edges) {
            snaps.push_back(uf.snapshot());
            for (auto &&[u, v] : edges) uf.unite(u, v);
            for (auto &&event : seg_adds[k]) uf.add_value(event.v, event.x);
        },
        [&](int, const vector<pair<int, int>> &) {
            uf.rollback(snaps.back());
            snaps.pop_back();
        },
        [&](int t) {
            if (type[t] == 3) ans.push_back(uf.get_sum(query_vertex[t]));
        }
    );

    for (auto &&x : ans) pr.writeln(x);
    return 0;
}
