#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/challenges/sources/PCK/Final/0403"
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <numeric>
#include <bitset>
#include <cmath>

static const int MOD = 1000000007;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
using namespace std;

template<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;

#include "../graph/manhattanmst.cpp"
#include "../datastructure/unionfind.cpp"

int main() {
    int n;
    cin >> n;
    vector<int> xs(n), ys(n);
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        xs[i] = x+y, ys[i] = x-y;
    }
    auto res = manhattanMST(xs, ys);
    vector<pair<int, pair<int, int>>> r(res.size());
    for (int i = 0; i < res.size(); ++i) {
        auto &&x = res[i];
        r[i] = {abs(xs[x.first]-xs[x.second])+abs(ys[x.first]-ys[x.second]), {x.first, x.second}};
    }
    sort(r.begin(),r.end());
    UnionFind uf(n);
    ll ans = 0;
    for (auto &&i : r) {
        pair<int, int> p; tie(ignore, p) = i;
        if(uf.unite(p.first, p.second)) ans += i.first;
    }
    cout << ans/2 << "\n";
    return 0;
}
