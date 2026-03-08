#define PROBLEM "https://judge.yosupo.jp/problem/minimum_spanning_tree"

#include <algorithm>
#include <vector>
using namespace std;

using ll = long long;

#include "../util/fastio.cpp"
#include "../graph/kruskal.cpp"

int main() {
    Scanner in;
    Printer out;

    int n, m;
    in.read(n, m);
    vector<edge<ll>> edges;
    edges.reserve(m);
    for (int i = 0; i < m; ++i) {
        int u, v;
        ll w;
        in.read(u, v, w);
        edges.emplace_back(u, v, w, i);
    }
    auto res = kruskal(edges, n);
    if (!res.exists) return 0;
    out.writeln(res.cost);
    for (int i = 0; i < (int)res.edge_id.size(); ++i) {
        if (i) out.write(' ');
        out.write(res.edge_id[i]);
    }
    out.writeln();
    return 0;
}
