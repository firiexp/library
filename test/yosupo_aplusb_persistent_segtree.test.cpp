#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../datastructure/segmenttree/persistent_segtree.cpp"

struct Monoid {
    using T = string;
    static T f(const T &a, const T &b) { return a + b; }
    static T e() { return ""; }
};

void self_check() {
    PersistentSegmentTree<Monoid> large(1000000000);
    assert(large.node.size() == 1);
    int a = large.update(0, 0, "a");
    int b = large.add(a, 999999999, "z");
    int c = large.update(0, 500000000, "m");
    assert(large.query(0, 0, 1000000000) == "");
    assert(large.query(b, 0, 1000000000) == "az");
    assert(large.query(b, 1, 999999999) == "");
    assert(large.query(c, 0, 1000000000) == "m");
    assert(large.get(a, 999999999) == "" && large.get(b, 0) == "a");
    assert(large.node.size() <= 94);

    mt19937 rng(166);
    for (int n = 0; n <= 35; ++n) for (bool from_array : {false, true}) {
        vector<string> initial(n);
        if (from_array) for (auto &s : initial) s = string(1, 'a' + rng() % 26);
        auto seg = from_array ? PersistentSegmentTree<Monoid>(initial) : PersistentSegmentTree<Monoid>(n);
        assert(seg.node.size() == (size_t)(from_array && n ? 2 * n - 1 : 1));
        vector<vector<string>> versions{initial};
        for (int step = 0; step < 180; ++step) {
            int t = rng() % 2 ? seg.latest_version() : rng() % versions.size();
            int k = n ? rng() % n : 0;
            string s(1, 'a' + rng() % 26);
            auto next = versions[t];
            int at;
            if (step % 2) {
                at = t == seg.latest_version() ? seg.add(k, s) : seg.add(t, k, s);
                if (n) next[k] += s;
            } else {
                at = t == seg.latest_version() ? seg.update(k, s) : seg.update(t, k, s);
                if (n) next[k] = s;
            }
            assert(at == (int)versions.size());
            versions.push_back(next);
            assert(seg.versions() == (int)versions.size() && seg.latest_version() == at);
            size_t nodes = seg.node.size();
            for (int q = 0; q < 15; ++q) {
                int v = q == 0 ? t : q == 1 ? at : rng() % versions.size();
                int l = rng() % (n + 1), r = rng() % (n + 1);
                if (l > r) swap(l, r);
                string expected;
                for (int i = l; i < r; ++i) expected += versions[v][i];
                assert(seg.query(v, l, r) == expected);
                if (v == at) assert(seg.query(l, r) == expected);
                if (n) assert(seg.get(v, k) == versions[v][k]);
            }
            if (n) assert(seg[k] == next[k]);
            assert(seg.node.size() == nodes);
        }
    }
}

int main() {
    self_check();
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
