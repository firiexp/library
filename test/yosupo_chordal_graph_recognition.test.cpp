#define PROBLEM "https://judge.yosupo.jp/problem/chordal_graph_recognition"

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../graph/chordal_graph.cpp"

int main() {
    Scanner in;
    Printer out;
    int n, m;
    in.read(n, m);
    vector<pair<int, int>> edges(m);
    for (auto &[u, v] : edges) in.read(u, v);
    auto result = recognize_chordal(n, edges);
    if (result.chordal) {
        out.println("YES");
        out.println(result.peo);
    } else {
        out.println("NO");
        out.println(result.induced_cycle.size());
        out.println(result.induced_cycle);
    }
}
