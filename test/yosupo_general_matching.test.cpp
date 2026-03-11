#define PROBLEM "https://judge.yosupo.jp/problem/general_matching"

#include <utility>
#include <vector>
using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../graph/general_matching.cpp"

int main() {
    Scanner in;
    Printer out;
    int n, m;
    in.read(n, m);
    GeneralMatching gm(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        in.read(u, v);
        gm.add_edge(u, v);
    }
    int ans = gm.max_matching();
    out.writeln(ans);
    for (auto&& [u, v] : gm.get_pairs()) {
        out.writeln(u, v);
    }
    return 0;
}
