#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path"

#include <algorithm>
#include <cassert>
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
#include "../graph/shortest_path/generated_shortest_path.cpp"

int main() {
    Scanner in;
    Printer out;

    int n, m, s, t;
    in.read(n, m, s, t);
    vector<vector<pair<int, ll>>> G(n);
    for (int i = 0; i < m; ++i) {
        array<int, 3> e;
        in.read(e);
        G[e[0]].emplace_back(e[1], e[2]);
    }
    auto res = dijkstra_generated_to<ll>(n, s, t, [&](int v, auto emit) {
        for (auto [to, cost] : G[v]) emit(to, cost);
    });
    if (res.dist == INF<ll>) {
        out.println(-1);
        return 0;
    }
    const auto &path = res.path;
    out.println(res.dist, (int)path.size() - 1);
    for (int i = 0; i + 1 < (int)path.size(); ++i) {
        out.println(array<int, 2>{path[i], path[i + 1]});
    }
    return 0;
}
