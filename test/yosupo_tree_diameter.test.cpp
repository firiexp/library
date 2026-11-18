#define PROBLEM "https://judge.yosupo.jp/problem/tree_diameter"

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>
using namespace std;

using ll = long long;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include <charconv>
#include "../util/fastio.cpp"
#include "../tree/diameter_weighted.cpp"

int main() {
    Scanner sc;
    Printer pr;

    int n;
    sc.read(n);
    vector<vector<pair<int, ll>>> g(n);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        ll c;
        sc.read(a, b, c);
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }

    auto [dist, path] = tree_diameter_weighted_path(g);
    pr.println(dist, (int)path.size());
    pr.println(path);
    return 0;
}
