#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../datastructure/persistent_unionfind.cpp"

int root(const vector<int> &p, int v) {
    while (p[v] >= 0) v = p[v];
    return v;
}

void check() {
    PersistentUnionFind empty(0);
    assert(empty.count() == 0);
    assert(empty.copy_version(0) == 1);
    assert(empty.unite(0, 0, 0) == 2);
    assert(empty.count(1) == 0 && empty.count(2) == 0);
    PersistentUnionFind split(17);
    int a = split.unite(0, 0, 16);
    int b = split.unite(0, 0, 1);
    int c = split.unite(b, 2, 1);
    assert(split.root(a, 16) == 0 && split.root(c, 2) == 0);
    assert(split.size(a, 0) == 2 && split.size(b, 0) == 2 && split.size(c, 0) == 3);
    assert(!split.same(b, 0, 16) && !split.same(a, 0, 1));

    mt19937 rng(120);
    for (int tc = 0; tc < 1000; ++tc) {
        int n = 1 + tc % 64;
        PersistentUnionFind uf(n);
        vector<vector<int>> versions(1, vector<int>(n, -1));
        for (int step = 0; step < 300; ++step) {
            int t = rng() % 3 == 0 ? uf.latest_version() : rng() % versions.size();
            int u = rng() % n, v = rng() % n;
            auto p = versions[t];
            int next;
            if (rng() % 5 == 0) {
                next = uf.copy_version(t);
            } else {
                next = t == uf.latest_version() && step % 2 == 0 ? uf.unite(u, v) : uf.unite(t, u, v);
                int ru = root(p, u), rv = root(p, v);
                if (ru != rv) {
                    if (p[ru] > p[rv]) swap(ru, rv);
                    p[ru] += p[rv];
                    p[rv] = ru;
                }
            }
            assert(next == int(versions.size()) && next == uf.latest_version());
            versions.push_back(p);
            assert(uf.versions() == int(versions.size()));
            for (int q = 0; q < 10; ++q) {
                int at = q == 0 ? t : q == 1 ? next : rng() % versions.size();
                int x = rng() % n, y = rng() % n;
                const auto &expected = versions[at];
                int rx = root(expected, x), ry = root(expected, y);
                assert(uf.root(at, x) == rx);
                assert(uf.same(at, x, y) == (rx == ry));
                assert(uf.size(at, x) == -expected[rx]);
                assert(uf.count(at) == count_if(expected.begin(), expected.end(), [](int z) { return z < 0; }));
            }
            assert(uf.root(u) == root(p, u));
            assert(uf.same(u, v) == (root(p, u) == root(p, v)));
            assert(uf.size(u) == -p[root(p, u)]);
            assert(uf.count() == uf.count(next));
        }
    }
}

int main() {
    check();
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
