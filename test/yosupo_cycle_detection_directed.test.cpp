#define PROBLEM "https://judge.yosupo.jp/problem/cycle_detection"

#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../graph/cycle_detection_directed.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int n, m;
    sc.read(n, m);
    vector<vector<pair<int, int>>> g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        sc.read(u, v);
        g[u].push_back({v, i});
    }
    auto cyc = cycle_detection_directed(g);
    if (cyc.empty()) {
        pr.println(-1);
        return 0;
    }
    pr.println((int)cyc.size());
    for (int id : cyc) pr.println(id);
    return 0;
}
