#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include <algorithm>
#include <cstddef>
#include <numeric>
#include <vector>
using namespace std;

#include "../datastructure/quickfind.cpp"
#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"

int main() {
    Scanner in;
    Printer out;

    int n, q;
    in.read(n, q);
    QuickFind uf(n);
    for (int i = 0; i < q; ++i) {
        int t, u, v;
        in.read(t, u, v);
        if (t) out.writeln(uf.same(u, v));
        else uf.unite(u, v);
    }
    return 0;
}
