#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_1_B"

#include <limits>
#include <vector>
using namespace std;

using ll = long long;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../graph/bellman_ford.cpp"

int main() {
    Scanner sc;
    Printer pr;

    int n, m, s;
    sc.read(n, m, s);
    vector<edge<ll>> es;
    es.reserve(m);
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        sc.read(a, b, c);
        es.emplace_back(a, b, c);
    }

    auto dist = bellman_ford(s, n, es);
    if (dist.empty()) {
        pr.println("NEGATIVE CYCLE");
        return 0;
    }

    constexpr ll INF = numeric_limits<ll>::max();
    for (int i = 0; i < n; ++i) {
        if (dist[i] == INF) pr.println("INF");
        else pr.println(dist[i]);
    }
    return 0;
}
