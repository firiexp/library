#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_1_C"

#include <bits/stdc++.h>
using namespace std;
template <class T> constexpr T INF = numeric_limits<T>::max() / 32 * 15 + 208;

#include "../util/fastio.cpp"
#include "../graph/shortest_path/floyd_warshall.cpp"

int main() {
    Scanner in;
    Printer out;
    int n, m;
    in.read(n, m);
    vector<edge<long long>> edges;
    edges.reserve(m);
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        in.read(u, v, w);
        edges.emplace_back(u, v, w);
    }
    auto dist = floyd_warshall(n, edges);
    if (dist.empty()) {
        out.println("NEGATIVE CYCLE");
        return 0;
    }
    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            if (v) out.print(' ');
            if (dist[u][v] == INF<long long>) out.print("INF");
            else out.print(dist[u][v]);
        }
        out.println();
    }
}
