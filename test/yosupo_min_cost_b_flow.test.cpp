#define PROBLEM "https://judge.yosupo.jp/problem/min_cost_b_flow"
#include <bits/stdc++.h>

using ll = long long;
using namespace std;

#include "../util/fastio.cpp"
#include "../graph/minimum_cost_b_flow.cpp"

void write_i128(Printer& pr, __int128_t x) {
    if(x == 0) {
        pr.write('0');
        return;
    }
    if(x < 0) {
        pr.write('-');
        x = -x;
    }
    string s;
    while(x > 0) {
        s.push_back(char('0' + x % 10));
        x /= 10;
    }
    reverse(s.begin(), s.end());
    pr.write(s);
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
        pr.writeln("infeasible");
        return 0;
    }

    write_i128(pr, cost);
    pr.writeln();
    auto potential = mcf.get_potential();
    for (int i = 0; i < n; ++i) {
        pr.write(potential[i]);
        pr.write(i + 1 == n ? '\n' : ' ');
    }
    auto flow = mcf.get_flows();
    for (int i = 0; i < m; ++i) {
        pr.writeln(flow[i]);
    }
    return 0;
}
