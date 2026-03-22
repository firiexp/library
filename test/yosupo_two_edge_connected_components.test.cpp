#define PROBLEM "https://judge.yosupo.jp/problem/two_edge_connected_components"

#include <algorithm>
#include <vector>
using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../graph/twoedgeconnectedcomponents.cpp"

int main() {
    Scanner sc;
    Printer pr;

    int n, m;
    sc.read(n, m);
    TwoEdgeConnectedComponents g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        sc.read(u, v);
        g.add_edge(u, v);
    }

    int k = g.build();
    auto comp = g.out;
    for (auto &&v : comp) sort(v.begin(), v.end());
    sort(comp.begin(), comp.end());

    pr.println(k);
    for (auto &&v : comp) {
        pr.print((int)v.size());
        for (auto &&x : v) {
            pr.print(' ');
            pr.print(x);
        }
        pr.println();
    }
    return 0;
}
