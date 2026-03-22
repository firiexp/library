#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"

#include <queue>
#include <utility>
#include <vector>
using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../graph/hopcroft_karp.cpp"

int main() {
    Scanner in;
    Printer out;
    int l, r, m;
    in.read(l, r, m);
    HopcroftKarp hk(l, r);
    for (int i = 0; i < m; ++i) {
        int a, b;
        in.read(a, b);
        hk.add_edge(a, b);
    }
    int ans = hk.max_matching();
    out.println(ans);
    auto pairs = hk.get_pairs();
    for (auto&& [a, b] : pairs) {
        out.println(a, b);
    }
    return 0;
}

