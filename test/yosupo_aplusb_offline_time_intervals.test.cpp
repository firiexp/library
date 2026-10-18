#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../util/offline_time_intervals.cpp"
#include "../datastructure/undoable_weighted_unionfind.cpp"

struct XorGroup {
    using T = int;
    static T op(T a, T b) { return a ^ b; }
    static T inv(T a) { return a; }
    static T e() { return 0; }
};

void check(const UndoableWeightedUnionFind<XorGroup> &uf, int n,
           const vector<array<int, 3>> &edges) {
    vector<vector<pair<int, int>>> g(n);
    for (auto [u, v, w] : edges) {
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    vector<int> color(n, -1), component(n), bad(n);
    for (int s = 0; s < n; ++s) {
        if (color[s] != -1) continue;
        vector<int> queue{s};
        color[s] = 0;
        component[s] = s;
        for (int i = 0; i < (int)queue.size(); ++i) {
            int v = queue[i];
            for (auto [u, w] : g[v]) {
                if (color[u] == -1) {
                    color[u] = color[v] ^ w;
                    component[u] = s;
                    queue.push_back(u);
                } else if ((color[u] ^ color[v]) != w) bad[s] = 1;
            }
        }
    }
    assert(uf.consistent() == (count(bad.begin(), bad.end(), 1) == 0));
    for (int u = 0; u < n; ++u) {
        assert(uf.consistent(u) == !bad[component[u]]);
        for (int v = 0; v < n; ++v) {
            bool same = component[u] == component[v];
            assert(uf.same(u, v) == same);
            auto delta = uf.diff(u, v);
            assert(delta.has_value() == (same && !bad[component[u]]));
            if (delta) assert(*delta == (color[u] ^ color[v]));
        }
    }
}

int main() {
    mt19937 rng(156);
    for (int tc = 0; tc < 1500; ++tc) {
        int n = 1 + rng() % 8, q = rng() % 26, k = rng() % 36;
        vector<array<int, 3>> events(1 + rng() % 24), intervals;
        for (auto &[u, v, w] : events) u = rng() % n, v = rng() % n, w = rng() % 2;
        OfflineTimeIntervals tm(q);
        for (int i = 0; i < k; ++i) {
            int l = rng() % (q + 1), r = rng() % (q + 1), id = rng() % events.size();
            if (l > r) swap(l, r);
            intervals.push_back({l, r, id});
            tm.add_interval(l, r, id);
        }
        UndoableWeightedUnionFind<XorGroup> uf(n);
        vector<array<int, 3>> base{events[0]};
        uf.unite(events[0][0], events[0][1], events[0][2]);
        for (int run = 0; run < 2; ++run) {
            int t = 0, snapshots = 0;
            vector<int> history, active(events.size());
            tm.run([&] { ++snapshots; return make_pair(uf.get_state(), history.size()); },
                [&](int id) {
                    auto [u, v, w] = events[id];
                    uf.unite(u, v, w);
                    history.push_back(id);
                    ++active[id];
                },
                [&](pair<int, size_t> state) {
                    uf.rollback(state.first);
                    while (history.size() > state.second) {
                        --active[history.back()];
                        history.pop_back();
                    }
                },
                [&](int time) {
                    assert(time == t++);
                    auto expected = base;
                    vector<int> counts(events.size());
                    for (auto [l, r, id] : intervals) {
                        if (l <= time && time < r) {
                            expected.push_back(events[id]);
                            ++counts[id];
                        }
                    }
                    assert(counts == active);
                    check(uf, n, expected);
                });
            assert(t == q && history.empty() && uf.get_state() == 1);
            assert(count(active.begin(), active.end(), 0) == (int)active.size());
            if (q == 0) assert(snapshots == 0);
            check(uf, n, base);
        }
    }
    int q = 100001, k = 100000, width = 12345, sum = 7, time = 0;
    OfflineTimeIntervals tm(q);
    for (int i = 0; i < k; ++i) tm.add_interval(i, min(q, i + width), i);
    tm.run([&] { return sum; }, [&](int) { ++sum; }, [&](int state) { sum = state; },
        [&](int t) {
            assert(t == time++);
            assert(sum == 7 + min(t + 1, k) - max(0, t - width + 1));
        });
    assert(sum == 7 && time == q);
}
