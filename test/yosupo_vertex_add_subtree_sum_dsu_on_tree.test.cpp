#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../datastructure/binaryindexedtree.cpp"
#include "../tree/dsu_on_tree.cpp"

struct Query {
    int time, type;
    ll x;
};

int main() {
    Scanner sc;
    Printer pr;

    int n, q;
    sc.read(n, q);
    vector<ll> a(n);
    for (auto &&x : a) sc.read(x);

    vector<vector<int>> g(n);
    for (int v = 1; v < n; ++v) {
        int p;
        sc.read(p);
        g[p].push_back(v);
        g[v].push_back(p);
    }

    vector<vector<Query>> qs(n);
    vector<ll> ans(q, -1);
    for (int i = 0; i < q; ++i) {
        int t, v;
        sc.read(t, v);
        if (t == 0) {
            ll x;
            sc.read(x);
            qs[v].push_back({i, 0, x});
        } else {
            qs[v].push_back({i, 1, 0});
        }
    }

    BIT<ll> bit(q + 1);
    vector<pair<int, ll>> history;
    ll base = 0;

    auto add = [&](int v) {
        base += a[v];
        for (auto &&qu : qs[v]) {
            if (qu.type == 0) {
                bit.add(qu.time, qu.x);
                history.push_back({qu.time, qu.x});
            }
        }
    };
    auto query = [&](int v) {
        for (auto &&qu : qs[v]) {
            if (qu.type == 1) ans[qu.time] = base + bit.sum(qu.time);
        }
    };
    auto reset = [&]() {
        base = 0;
        for (auto &&[t, x] : history) bit.add(t, -x);
        history.clear();
    };

    DSUonTree dsu(g);
    dsu.run_add_reset(add, query, reset);

    for (auto &&x : ans) {
        if (x != -1) pr.println(x);
    }
    return 0;
}
