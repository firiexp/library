#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path"

#include <algorithm>
#include <array>
#include <limits>
#include <tuple>
#include <vector>
using namespace std;

using ll = long long;
template<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../graph/dijkstra_radix_heap.cpp"

int main() {
    Scanner sc;
    Printer pr;

    int n, m, s, t;
    sc.read(n, m, s, t);
    vector<vector<edge<ll>>> G(n), Ginv(n);
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        sc.read(a, b, c);
        G[a].emplace_back(b, c);
        Ginv[b].emplace_back(a, c);
    }
    auto d = dijkstra(s, G);
    if (d[t] == INF<ll>) {
        pr.writeln(-1);
        return 0;
    }
    vector<int> ans{t};
    vector<int> visited(n);
    visited[t] = 1;
    while (ans.back() != s) {
        for (auto &&i : Ginv[ans.back()]) {
            if (d[i.to] + i.cost == d[ans.back()] && !visited[i.to]) {
                ans.emplace_back(i.to);
                visited[i.to] = 1;
                break;
            }
        }
    }
    pr.writeln(d[t], (int)ans.size() - 1);
    for (int i = (int)ans.size()-1; i > 0; --i) {
        pr.writeln(ans[i], ans[i - 1]);
    }
    return 0;
}
