#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum"

#include <algorithm>
#include <map>
#include <utility>
#include <vector>
using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../graph/dynamic_graph_vertex_add_component_sum.cpp"

int main() {
    Scanner sc;
    Printer pr;

    int n, q;
    sc.read(n, q);
    vector<long long> a(n);
    for (auto &x : a) sc.read(x);

    DynamicGraphVertexAddComponentSum solver(a, q);
    for (int i = 0; i < q; ++i) {
        int t;
        sc.read(t);
        if (t == 0) {
            int u, v;
            sc.read(u, v);
            solver.add_edge(u, v);
        } else if (t == 1) {
            int u, v;
            sc.read(u, v);
            solver.erase_edge(u, v);
        } else if (t == 2) {
            int v;
            long long x;
            sc.read(v, x);
            solver.add_vertex(v, x);
        } else {
            int v;
            sc.read(v);
            solver.add_component_query(v);
        }
    }

    auto ans = solver.solve();
    for (auto &&x : ans) pr.writeln(x);
    return 0;
}
