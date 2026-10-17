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

template<class M, class F>
void check_search(const PersistentSegmentTree<M> &seg, int version,
                  const vector<typename M::T> &a, int end, F cond) {
    int left = end, right = end;
    auto acc = M::e();
    while(left && cond(M::f(a[left - 1], acc))) acc = M::f(a[--left], acc);
    acc = M::e();
    while(right < int(a.size()) && cond(M::f(acc, a[right]))) acc = M::f(acc, a[right++]);
    size_t nodes = seg.node.size(), roots = seg.root.size();
    auto before = seg.query(version, 0, seg.n);
    assert(seg.search_left(version, end, cond) == left);
    assert(seg.search_right(version, end, cond) == right);
    if(version == seg.latest_version()) {
        assert(seg.search_left(end, cond) == left);
        assert(seg.search_right(end, cond) == right);
    }
    assert(seg.node.size() == nodes && seg.root.size() == roots);
    assert(seg.query(version, 0, seg.n) == before);
}

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
    auto empty = [](const string &s) { return s.empty(); };
    for(int end : {0, 500000000, 1000000000}) {
        assert(large.search_right(0, end, empty) == 1000000000);
        assert(large.search_left(0, end, empty) == 0);
    }
    assert(large.search_right(b, 0, empty) == 0);
    assert(large.search_right(b, 1, empty) == 999999999);
    assert(large.search_left(b, 1000000000, empty) == 1000000000);
    assert(large.search_left(b, 999999999, empty) == 1);
    assert(large.search_right(c, 0, empty) == 500000000);
    assert(large.search_left(c, 1000000000, empty) == 500000001);
    assert(large.node.size() <= 94);

    mt19937 rng(166);
    for (int n = 0; n <= 35; ++n) for (bool from_array : {false, true}) {
        vector<string> initial(n);
        if (from_array) for (auto &s : initial) s = string(1, 'a' + rng() % 3);
        auto seg = from_array ? PersistentSegmentTree<Monoid>(initial) : PersistentSegmentTree<Monoid>(n);
        assert(seg.node.size() == (size_t)(from_array && n ? 2 * n - 1 : 1));
        vector<vector<string>> versions{initial};
        for(int end = 0; end <= n; ++end) check_search(seg, 0, initial, end, empty);
        for (int step = 0; step < 180; ++step) {
            int t = rng() % 2 ? seg.latest_version() : rng() % versions.size();
            int k = n ? rng() % n : 0;
            string s(1, 'a' + rng() % 3);
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
                int limit = rng() % (2 * n + 1);
                auto cond = [&](const string &x) {
                    return int(x.size()) <= limit && x.find("ab") == string::npos;
                };
                check_search(seg, v, versions[v], q % 3 == 0 ? 0 : q % 3 == 1 ? n : l, cond);
            }
            if (n) assert(seg[k] == next[k]);
            assert(seg.node.size() == nodes);
        }
    }
}

struct Sum {
    using T = long long;
    static T e() { return 0; }
    static T f(T a, T b) { return a + b; }
};

void sum_check() {
    mt19937 rng(206);
    for(int n : {0, 1, 2, 3, 7, 8, 9, 31, 32, 33, 65}) {
        PersistentSegmentTree<Sum> seg(n);
        vector<vector<long long>> versions(1, vector<long long>(n));
        for(int step = 0; step < 200; ++step) {
            int t = rng() % versions.size(), k = n ? rng() % n : 0;
            auto a = versions[t];
            long long value = rng() % 20;
            if(n) a[k] = value;
            int id = seg.update(t, k, value);
            assert(id == int(versions.size()));
            versions.push_back(a);
            for(int q = 0; q < 10; ++q) {
                int v = q == 0 ? id : rng() % versions.size();
                long long limit = q == 0 ? 0 : q == 1 ? 20 * n : rng() % (20 * n + 1);
                auto cond = [&](long long x) { return x <= limit; };
                check_search(seg, v, versions[v], rng() % (n + 1), cond);
            }
        }
    }
}

int main() {
    self_check();
    sum_check();
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
