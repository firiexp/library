#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_1_B"

#include <limits>
#include <vector>
using namespace std;

using ll = long long;
template<class T> constexpr T INF = ::numeric_limits<T>::max() / 32 * 15 + 208;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../graph/bellman_ford_negative_loop.cpp"

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
    for (int i = 0; i < n; ++i) {
        if (dist[i] == -INF<ll>) {
            pr.writeln("NEGATIVE CYCLE");
            return 0;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (dist[i] == INF<ll>) pr.writeln("INF");
        else pr.writeln(dist[i]);
    }
    return 0;
}
