#define PROBLEM "https://judge.yosupo.jp/problem/directedmst"

#include <vector>
using ll = long long;
using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../graph/chu_liu_edmonds.cpp"

int main() {
    Scanner in;
    Printer out;
    int n, m, r;
    in.read(n, m, r);
    ChuLiuEdmonds<ll> dmst(n, r);
    for (int i = 0; i < m; ++i) {
        int a, b;
        ll c;
        in.read(a, b, c);
        dmst.add_edge(a, b, c);
    }
    auto res = dmst.solve();
    if (!res.exists) return 0;
    out.writeln(res.cost);
    for (int i = 0; i < n; ++i) {
        if (i) out.write(' ');
        out.write(res.parent[i]);
    }
    out.writeln();
    return 0;
}

