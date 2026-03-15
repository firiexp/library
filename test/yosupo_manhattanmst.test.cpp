#define PROBLEM "https://judge.yosupo.jp/problem/manhattanmst"

#include <algorithm>
#include <cstdlib>
#include <map>
#include <numeric>
#include <tuple>
#include <vector>
using namespace std;

using ll = long long;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../graph/manhattanmst.cpp"
#include "../datastructure/unionfind.cpp"

int main() {
    Scanner sc;
    Printer pr;

    int n;
    sc.read(n);
    vector<ll> xs(n), ys(n);
    for (int i = 0; i < n; ++i) sc.read(xs[i], ys[i]);

    auto cand = manhattanMST(xs, ys);
    vector<tuple<ll, int, int>> edges;
    edges.reserve(cand.size());
    for (auto [u, v] : cand) {
        ll cost = llabs(xs[u] - xs[v]) + llabs(ys[u] - ys[v]);
        edges.emplace_back(cost, u, v);
    }
    sort(edges.begin(), edges.end());

    UnionFind uf(n);
    vector<pair<int, int>> used;
    ll total = 0;
    for (auto [cost, u, v] : edges) {
        if (!uf.unite(u, v)) continue;
        total += cost;
        used.emplace_back(u, v);
    }

    pr.writeln(total);
    for (auto [u, v] : used) pr.writeln(u, v);
    return 0;
}
