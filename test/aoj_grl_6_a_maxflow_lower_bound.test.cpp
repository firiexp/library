#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A"
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

#include "../graph/maxflow_lower_bound.cpp"

int main() {
    int n, m;
    cin >> n >> m;
    MaxFlowLowerBound<ll> g(n);
    for(int i = 0; i < m; ++i) {
        int u, v;
        ll c;
        cin >> u >> v >> c;
        g.add_edge(u, v, 0, c);
    }
    auto res = g.max_flow(0, n - 1);
    if(!res.first) {
        cout << -1 << '\n';
        return 0;
    }
    cout << res.second << '\n';
    return 0;
}
