#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path"

#include <algorithm>
#include <array>
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

#include <charconv>
#include "../util/fastio.cpp"
#include "../graph/shortest_path/dijkstra_restore.cpp"

int main() {
    Scanner in;
    Printer out;

    int n, m, s, t;
    in.read(n, m, s, t);
    vector<edge<ll>> edges;
    edges.reserve(m);
    for (int i = 0; i < m; ++i) {
        array<int, 3> e;
        in.read(e);
        edges.emplace_back(e[0], e[1], e[2]);
    }
    auto res = dijkstra_restore(s, n, edges);
    if (res.dist[t] == INF<ll>) {
        out.println(-1);
        return 0;
    }
    auto path = restore_edge_path(s, t, res);
    out.println(res.dist[t], (int)path.size());
    for (int id : path) {
        out.println(array<int, 2>{edges[id].from, edges[id].to});
    }
    return 0;
}
