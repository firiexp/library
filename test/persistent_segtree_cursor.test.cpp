#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../datastructure/segmenttree/persistent_segtree.cpp"

struct Sum {
    using T = int;
    static T f(T a, T b) { return a + b; }
    static T e() { return 0; }
};
using Tree = PersistentSegmentTree<Sum>;

int kth(const Tree &seg, vector<pair<Tree::Cursor, int>> cursors, int k) {
    int total = 0;
    for (auto [cur, sign] : cursors) total += sign * cur.fold();
    assert(0 <= k && k < total);
    size_t nodes = seg.node.size();
    int versions = seg.versions();
    while (!cursors[0].first.is_leaf()) {
        int low = 0;
        for (auto [cur, sign] : cursors) low += sign * seg.split(cur).low.fold();
        assert(0 <= low && low <= total);
        bool go_low = k < low;
        if (!go_low) k -= low;
        total = go_low ? low : total - low;
        for (auto &[cur, sign] : cursors) {
            auto children = seg.split(cur);
            cur = go_low ? children.low : children.high;
        }
    }
    int result = cursors[0].first.index();
    for (auto [cur, sign] : cursors) assert(cur.index() == result);
    assert(seg.node.size() == nodes && seg.versions() == versions);
    return result;
}

struct Concatenate {
    using T = string;
    static T f(const T &a, const T &b) { return a + b; }
    static T e() { return ""; }
};

int main() {
    for (bool from_array : {false, true}) {
        Tree empty = from_array ? Tree(vector<int>{}) : Tree(0);
        auto cur = empty.root_cursor();
        assert(cur.empty() && !cur.is_leaf() && cur.fold() == 0);
        assert(cur.range() == make_pair(0, 0));
    }
    Tree large(1000000000);
    auto cur = large.root_cursor();
    while (!cur.is_leaf()) cur = large.split(cur).high;
    assert(cur.index() == 999999999 && cur.fold() == 0);
    assert(large.node.size() == 1 && large.versions() == 1);
    large.add(0, 999999999, 7);
    assert(cur.index() == 999999999 && cur.fold() == 0);

    vector<string> words = {"a", "bc", "", "d", "ef"};
    PersistentSegmentTree<Concatenate> strings(words);
    auto visit = [&](auto &&self, auto cursor) -> void {
        auto [l, r] = cursor.range();
        assert(cursor.fold() == accumulate(words.begin() + l, words.begin() + r, string()));
        assert(!cursor.empty());
        if (cursor.is_leaf()) assert(cursor.index() == l && r == l + 1);
        else {
            auto children = strings.split(cursor);
            assert(children.low.range().first == l && children.high.range().second == r);
            assert(children.low.range().second == children.high.range().first);
            self(self, children.low);
            self(self, children.high);
        }
    };
    visit(visit, strings.root_cursor());

    mt19937 rng(325);
    for (int n = 0; n <= 35; ++n) for (int domain : {1, 3, 8, 17}) {
        Tree seg(domain);
        vector<int> a(n);
        vector<Tree::Cursor> prefix{seg.root_cursor()};
        for (int &x : a) {
            x = rng() % domain;
            seg.add(x, 1);
            prefix.push_back(seg.root_cursor());
        }
        for (int l = 0; l <= n; ++l) for (int r = l; r <= n; ++r) {
            vector<int> sorted(a.begin() + l, a.begin() + r);
            sort(sorted.begin(), sorted.end());
            assert(prefix[r].fold() - prefix[l].fold() == r - l);
            for (int k = 0; k < r - l; ++k)
                assert(kth(seg, {{prefix[r], 1}, {prefix[l], -1}}, k) == sorted[k]);
        }
    }
    for (int tc = 0; tc < 100; ++tc) {
        int n = 1 + rng() % 35, domain = 1 + rng() % 20;
        Tree seg(domain);
        vector<int> parent(n, -1), depth(n), value(n), version(n);
        vector<Tree::Cursor> roots;
        auto zero = seg.root_cursor();
        for (int v = 0; v < n; ++v) {
            if (v) parent[v] = rng() % v, depth[v] = depth[parent[v]] + 1;
            value[v] = rng() % domain;
            version[v] = seg.add(v ? version[parent[v]] : 0, value[v], 1);
            roots.push_back(seg.root_cursor(version[v]));
        }
        for (int u = 0; u < n; ++u) for (int v = 0; v < n; ++v) {
            int a = u, b = v;
            vector<int> path;
            while (a != b) {
                if (depth[a] < depth[b]) swap(a, b);
                path.push_back(value[a]);
                a = parent[a];
            }
            path.push_back(value[a]);
            sort(path.begin(), path.end());
            auto before = parent[a] == -1 ? zero : roots[parent[a]];
            for (int k = 0; k < (int)path.size(); ++k)
                assert(kth(seg, {{roots[u], 1}, {roots[v], 1}, {roots[a], -1}, {before, -1}}, k) == path[k]);
        }
    }
}
