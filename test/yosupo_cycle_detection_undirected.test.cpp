#define PROBLEM "https://judge.yosupo.jp/problem/cycle_detection_undirected"

#include <utility>
#include <vector>
using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../graph/cycle_detection_undirected.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int n, m;
    sc.read(n, m);
    vector<pair<int, int>> edges(m);
    for (int i = 0; i < m; ++i) {
        sc.read(edges[i].first, edges[i].second);
    }
    auto res = cycle_detection_undirected(edges, n);
    if (res.vertices.empty()) {
        pr.println(-1);
        return 0;
    }
    int l = res.vertices.size();
    pr.println(l);
    for (int i = 0; i < l; ++i) {
        if (i) pr.print(' ');
        pr.print(res.vertices[i]);
    }
    pr.println();
    for (int i = 0; i < l; ++i) {
        if (i) pr.print(' ');
        pr.print(res.edge_ids[i]);
    }
    pr.println();
    return 0;
}
