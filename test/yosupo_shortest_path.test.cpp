#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path"

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
#include "../graph/dijkstra_restore.cpp"

int main() {
    Scanner in;
    Printer out;

    int n, m, s, t;
    in.read(n, m, s, t);
    vector<vector<edge<ll>>> G(n);
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        in.read(a, b, c);
        G[a].emplace_back(b, c);
    }
    auto res = dijkstra_restore(s, G);
    if (res.dist[t] == INF<ll>) {
        out.writeln(-1);
        return 0;
    }
    auto path = restore_path(s, t, res.parent);
    out.writeln(res.dist[t], (int)path.size() - 1);
    for (int i = 0; i + 1 < (int)path.size(); ++i) {
        out.writeln(path[i], path[i + 1]);
    }
    return 0;
}
