#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path"

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
using u32 = unsigned;
using u64 = unsigned long long;
using namespace std;

template<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;

#include "../graph/dijkstra.cpp"

int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    vector<vector<edge<ll>>> G(n), Ginv(n);
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        G[a].emplace_back(b, c);
        Ginv[b].emplace_back(a, c);
    }
    auto d = dijkstra(s, G);
    if(d[t] == INF<ll>){
        puts("-1");
        return 0;
    }
    vector<int> ans{t};
    vector<int> visited(n);
    visited[t] = 1;
    while(ans.back() != s){
        for (auto &&i : Ginv[ans.back()]) {
            if(d[i.to]+i.cost == d[ans.back()] && !visited[i.to]){
                ans.emplace_back(i.to);
                visited[i.to] = 1;
                break;
            }
        }
    }
    printf("%lld %lu\n", d[t], ans.size()-1);
    for (int i = (int)ans.size()-1; i > 0; --i) {
        printf("%d %d\n", ans[i], ans[i-1]);
    }
    return 0;
}