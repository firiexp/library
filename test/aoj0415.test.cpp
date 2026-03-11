#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0415"

#include <algorithm>
#include <vector>
using ll = long long;
using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../graph/bridge_tree.cpp"

int main() {
    Scanner sc;
    Printer pr;

    int n, m;
    sc.read(n, m);
    vector<int> V(n);
    for (auto &&i : V) sc.read(i);
    BridgeTree g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        sc.read(u, v);
        u--; v--;
        g.add_edge(u, v);
    }
    int k = g.build();
    vector<ll> v(k);
    for (int i = 0; i < k; ++i) {
        for (auto &&j : g.nodes[i]) {
            v[i] += V[j];
        }
    }
    ll ans = 0;
    auto dfs = [&](int x, int par, auto &&f) -> void {
        ll val1 = 0, val2 = 0;
        for (auto &&i : g.tree[x]) {
            if(i == par) continue;
            f(i, x, f);
            if(val1 <= v[i]){
                val2 = val1; val1 = v[i];
            }else if(val2 <= v[i]){
                val2 = v[i];
            }
        }
        ans = max(ans, val1+val2+v[x]);
        v[x] += val1;
    };
    dfs(0, -1, dfs);
    pr.writeln(ans);
    return 0;
}
