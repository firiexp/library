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

    pr.writeln(k);
    for (auto &&v : comp) {
        pr.write((int)v.size());
        for (auto &&x : v) {
            pr.write(' ');
            pr.write(x);
        }
        pr.writeln();
    }
    return 0;
}
