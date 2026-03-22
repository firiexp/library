#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_5_A"

#include <bits/stdc++.h>

using namespace std;

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
    vector<vector<pair<int, long long>>> g(n);
    for (int i = 0; i < n - 1; ++i) {
        int s, t, w;
        sc.read(s, t, w);
        g[s].push_back({t, w});
        g[t].push_back({s, w});
    }

    pr.println(tree_diameter_weighted(g).first);
    return 0;
}
