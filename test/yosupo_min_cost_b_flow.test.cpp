#define PROBLEM "https://judge.yosupo.jp/problem/min_cost_b_flow"
#include <bits/stdc++.h>

using ll = long long;
using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../graph/minimum_cost_b_flow.cpp"

void write_i128(Printer& pr, __int128_t x) {
    if(x == 0) {
        pr.print('0');
        return;
    }
    if(x < 0) {
        pr.print('-');
        x = -x;
    }
    string s;
    while(x > 0) {
        s.push_back(char('0' + x % 10));
        x /= 10;
    }
    reverse(s.begin(), s.end());
    pr.print(s);
}

int main() {
    Scanner sc;
    Printer pr;
    int n, m;
    sc.read(n, m);
    MinimumCostBFlow<ll, ll> mcf(n);
    for (int i = 0; i < n; ++i) {
        ll b;
        sc.read(b);
        mcf.add_supply(i, b);
    }
    for (int i = 0; i < m; ++i) {
        int s, t;
        ll lower, upper, cost;
        sc.read(s, t, lower, upper, cost);
        mcf.add_edge(s, t, lower, upper, cost);
    }

    auto [ok, cost] = mcf.solve();
    if(!ok) {
        pr.println("infeasible");
        return 0;
    }

    write_i128(pr, cost);
    pr.println();
    auto potential = mcf.get_potential();
    for (int i = 0; i < n; ++i) {
        pr.print(potential[i]);
        pr.print(i + 1 == n ? '\n' : ' ');
    }
    auto flow = mcf.get_flows();
    for (int i = 0; i < m; ++i) {
        pr.println(flow[i]);
    }
    return 0;
}
