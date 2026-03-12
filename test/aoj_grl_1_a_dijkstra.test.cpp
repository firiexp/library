#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_1_A"

#include <algorithm>
#include <limits>
#include <queue>
#include <tuple>
#include <vector>

using ll = long long;
using namespace std;

template<class T> constexpr T INF = numeric_limits<T>::max() / 32 * 15 + 208;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../graph/dijkstra.cpp"

int main() {
    Scanner in;
    Printer out;

    int n, m, s;
    in.read(n, m, s);
    vector<vector<edge<ll>>> G(n);
    for (int i = 0; i < m; ++i) {
        int u, v, c;
        in.read(u, v, c);
        G[u].emplace_back(v, c);
    }
    auto dist = dijkstra(s, G);
    for (int i = 0; i < n; ++i) {
        if (dist[i] == INF<ll>) out.writeln("INF");
        else out.writeln(dist[i]);
    }
    return 0;
}
