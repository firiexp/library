#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/0439"

#include <algorithm>
#include <functional>
#include <limits>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

template<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;

#include "../util/fastio.cpp"
#include "../tree/auxtree.cpp"

template <typename T>
using GPQ = priority_queue<T, vector<T>, greater<T>>;
int main() {
    Scanner sc;
    Printer pr;

    int n;
    sc.read(n);
    vector<vector<int>> color(n);
    AuxTree G(n);
    for (int i = 0; i < n; ++i) {
        int x;
        sc.read(x);
        color[x-1].emplace_back(i);
    }
    for (int i = 0; i < n-1; ++i) {
        int u, v;
        sc.read(u, v);
        u--; v--;
        G.add_edge(u, v);
    }
    G.buildLCA();
    vector<int> ans(n, INF<int>);
    vector<int> cmp(n), dist(n);
    for (auto &&v : color) {
        if(v.empty()) continue;
        int k = v.size();
        G.make(v);
        GPQ<pair<int, int>> Q;
        for (int i = 0; i < (int)v.size(); ++i) {
            if(i < k) dist[v[i]] = 0, cmp[v[i]] = v[i], Q.emplace(0, v[i]);
            else dist[v[i]] = INF<int>;
        }
        while(!Q.empty()){
            auto [d, i] = Q.top(); Q.pop();
            if(d != dist[i]) continue;
            for (auto &&j : G.out[i]) {
                if(dist[j] > dist[i] + G.distance(i, j)){
                    dist[j] = dist[i] + G.distance(i, j);
                    cmp[j] = cmp[i];
                    Q.emplace(dist[j], j);
                }
            }
        }
        for (auto &&i : v) {
            for (auto &&j : G.out[i]) {
                int l = cmp[i], r = cmp[j];
                if(l != r) ans[l] = min(ans[l], G.distance(l, r));
            }
        }
        G.clear(v);
    }
    for (auto &&i : ans) {
        pr.writeln(i);
    }
    return 0;
}
