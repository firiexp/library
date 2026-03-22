#define PROBLEM "https://judge.yosupo.jp/problem/tree_diameter"

#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

using ll = long long;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

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
