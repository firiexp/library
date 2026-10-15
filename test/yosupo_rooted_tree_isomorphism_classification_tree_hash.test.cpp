#define PROBLEM "https://judge.yosupo.jp/problem/rooted_tree_isomorphism_classification"

#include <algorithm>
#include <cassert>
#include <map>
#include <string>
#include <vector>
using namespace std;

using ll = long long;
using uint = unsigned;
using ull = unsigned long long;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include <charconv>
#include "../util/fastio.cpp"
#include "../tree/tree_hash.cpp"

int main() {
    Scanner sc;
    Printer pr;

    int n;
    sc.read(n);
    TreeHash th(n);
    for (int v = 1; v < n; ++v) {
        int p;
        sc.read(p);
        th.add_edge(p, v);
    }
    auto id = th.build(0);
    pr.println(th.kinds());
    for (int i = 0; i < n; ++i) {
        pr.print(id[i]);
        pr.print(i + 1 == n ? '\n' : ' ');
    }
    return 0;
}
