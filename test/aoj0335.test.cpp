#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0335"
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

template <typename T>
struct edge {
    int to; T cost, cost2;
    edge(int to, T cost, T cost2) : to(to), cost(cost), cost2(cost2) {}
};

#include "../util/makev.cpp"

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<edge<int>>> G(n);
    vector<int> deg(n), topo, ord(n);
    for (int i = 0; i < m; ++i) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        a--; b--;
        deg[b]++;
        G[a].emplace_back(b, c, d);
    }
    {
        queue<int> Q;
        Q.emplace(0);
        ord[0] = 0;
        int cur = 1;
        while(!Q.empty()){
            int i = Q.front(); Q.pop();
            topo.emplace_back(i);
            for (auto &&e : G[i]) {
                deg[e.to]--;
                if(!deg[e.to]) {
                    Q.emplace(e.to);
                    ord[e.to] = cur++;
                }
            }
        }
    }
    auto dp = make_v(n, n, INF<int>);
    dp[0][0] = 0;
    for (auto &&a : topo) {
        for (auto &&b : topo) {
            if(a == b) {
                for (auto &&i : G[a]) {
                    for (auto &&j : G[a]) {
                        if (i.to == j.to) {
                            chmin(dp[i.to][i.to], dp[a][b] + i.cost + i.cost2);
                        } else {
                            chmin(dp[i.to][j.to], dp[a][b] + i.cost + j.cost);
                        }
                    }
                }
            }else if(ord[a] < ord[b]){
                for (auto &&i : G[a]) {
                    chmin(dp[i.to][b], dp[a][b] + i.cost);
                }
            }else {
                for (auto &&i : G[b]) {
                    chmin(dp[a][i.to], dp[a][b] + i.cost);
                }
            }
        }
    }
    cout << dp.back().back() << "\n";
    return 0;
}