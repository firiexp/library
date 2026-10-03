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

void zero_weight_check() {
    vector<vector<pair<int, ll>>> g(4);
    for (int v = 1; v < 4; ++v) {
        g[0].push_back({v, 0});
        g[v].push_back({0, 0});
    }
    auto [zero, ends] = tree_diameter_weighted(g);
    assert(zero == 0);
    assert(0 <= ends.first && ends.first < 4 && 0 <= ends.second && ends.second < 4);
    g[0][1].second = g[2][0].second = 7;
    auto [dist, mixed] = tree_diameter_weighted(g);
    assert(dist == 7);
    assert((mixed.first == 2) != (mixed.second == 2));
}

int main() {
    zero_weight_check();
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

    auto [dist, ends] = tree_diameter_weighted(g);
    int s = ends.first;
    int t = ends.second;

    vector<int> parent(n, -1);
    vector<int> st = {s};
    parent[s] = s;
    while (!st.empty()) {
        int v = st.back();
        st.pop_back();
        if (v == t) break;
        for (auto [to, _] : g[v]) {
            if (parent[to] != -1) continue;
            parent[to] = v;
            st.push_back(to);
        }
    }

    vector<int> path;
    for (int v = t; v != s; v = parent[v]) path.push_back(v);
    path.push_back(s);
    reverse(path.begin(), path.end());

    pr.println(dist, (int)path.size());
    pr.println(path);
    return 0;
}
