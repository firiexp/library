#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <cassert>
#include <random>
#include <vector>
using namespace std;

using ll = long long;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../tree/dsu_on_tree.cpp"

bool is_ancestor(const vector<int> &parent, int a, int v) {
    while (v != -1) {
        if (v == a) return true;
        v = parent[v];
    }
    return false;
}

vector<ll> run_with_clear(const DSUonTree &dsu, const vector<ll> &w) {
    int n = w.size();
    vector<ll> ans(n, -1);
    ll cur = 0;
    auto update = [&](int v) {
        cur += w[v];
    };
    auto query = [&](int v) {
        ans[v] = cur;
    };
    auto clear = [&](int v) {
        cur -= w[v];
    };
    auto reset = [&]() {};
    dsu.run(update, query, clear, reset);
    return ans;
}

vector<ll> run_with_reset(const DSUonTree &dsu, const vector<ll> &w) {
    int n = w.size();
    vector<ll> ans(n, -1);
    ll cur = 0;
    auto update = [&](int v) {
        cur += w[v];
    };
    auto query = [&](int v) {
        ans[v] = cur;
    };
    auto clear = [&](int) {};
    auto reset = [&]() {
        cur = 0;
    };
    dsu.run(update, query, clear, reset);
    return ans;
}

void self_check() {
    mt19937 rng(0);
    for (int tc = 0; tc < 300; ++tc) {
        int n = rng() % 40 + 1;
        vector<int> parent(n, -1);
        vector<vector<int>> g(n);
        for (int v = 1; v < n; ++v) {
            parent[v] = rng() % v;
            g[parent[v]].push_back(v);
            g[v].push_back(parent[v]);
        }

        vector<ll> w(n);
        for (auto &&x : w) x = (int)(rng() % 2001) - 1000;

        vector<ll> want = w;
        vector<int> sub_size(n, 1);
        for (int v = n - 1; v >= 1; --v) {
            want[parent[v]] += want[v];
            sub_size[parent[v]] += sub_size[v];
        }

        DSUonTree dsu1(g, 0);
        DSUonTree dsu2(n);
        for (int v = 1; v < n; ++v) dsu2.add_edge(parent[v], v);
        dsu2.build(0);

        for (auto &&dsu : {dsu1, dsu2}) {
            assert(run_with_clear(dsu, w) == want);
            assert(run_with_reset(dsu, w) == want);
            for (int v = 0; v < n; ++v) {
                assert(dsu.end(v) - dsu.begin(v) == sub_size[v]);
                for (int u = 0; u < n; ++u) {
                    bool in = dsu.begin(v) <= dsu.idx(u) && dsu.idx(u) < dsu.end(v);
                    assert(in == is_ancestor(parent, v, u));
                }
            }
        }
    }
}

int main() {
    self_check();

    Scanner sc;
    Printer pr;
    ll a, b;
    sc.read(a, b);
    pr.println(a + b);
    return 0;
}
