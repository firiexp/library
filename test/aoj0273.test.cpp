#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0273"
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

#include "../geometry/dualgraph.cpp"

void solve(int n, int m){
    Polygon v(n);
    for (auto &&i : v) cin >> i;
    DualGraph G(v);
    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;
        G.add_edge(a, b);
    }
    G.build();
    int out = 0;
    for (int i = 0; i < G.A.size(); ++i) {
        if(area(G.A[i]) > 0) out = i;
    }
    vector<int> dist(G.A.size(), INF<int>);
    queue<int> Q;
    dist[out] = 0; Q.emplace(out);
    while(!Q.empty()){
        int i = Q.front(); Q.pop();
        for (auto &&j : G.G[i]) {
            if(dist[j] == INF<int>){
                dist[j] = dist[i]+1;
                Q.emplace(j);
            }
        }
    }
    cout << *max_element(dist.begin(),dist.end()) << "\n";
}

int main() {
    int n, m;
    while(cin >> n >> m, n){
        solve(n, m);
    }
    return 0;
}