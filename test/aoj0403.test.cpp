#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/challenges/sources/PCK/Final/0403"
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
    vector<int> xs(n), ys(n);
    for (int i = 0; i < n; ++i) {
        int x, y;
        sc.read(x, y);
        xs[i] = x+y, ys[i] = x-y;
    }
    auto res = manhattanMST(xs, ys);
    vector<tuple<int, int, int>> r(res.size());
    for (int i = 0; i < (int)res.size(); ++i) {
        auto &&x = res[i];
        r[i] = {abs(xs[x.first]-xs[x.second])+abs(ys[x.first]-ys[x.second]), x.first, x.second};
    }
    sort(r.begin(), r.end());
    UnionFind uf(n);
    ll ans = 0;
    for (auto &&i : r) {
        int cost, u, v;
        tie(cost, u, v) = i;
        if (uf.unite(u, v)) ans += cost;
    }
    pr.writeln(ans / 2);
    return 0;
}
