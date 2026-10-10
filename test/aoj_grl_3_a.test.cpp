#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../graph/lowlink.cpp"

int main() {
    Scanner in;
    Printer out;
    int n, m;
    in.read(n, m);
    LowLink g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        in.read(u, v);
        g.add_edge(u, v);
    }
    g.build();
    for (int v : g.articulation) out.println(v);
}
