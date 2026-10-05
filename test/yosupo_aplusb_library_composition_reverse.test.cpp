#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;

template<class T> constexpr T INF = numeric_limits<T>::max() / 32 * 15 + 208;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;

#include "../util/fastio.cpp"

#include "../graph/bellman_ford.cpp"
#include "../graph/bfs01.cpp"
#include "../graph/dijkstra.cpp"

#include "../graph/twosat.cpp"
#include "../graph/SCC.cpp"

#include "../graph/block_cut_tree.cpp"
#include "../graph/biconnected_components.cpp"

#include "../tree/virtual_tree_helper.cpp"
#include "../tree/auxtree.cpp"
#include "../tree/hld_edge.cpp"
#include "../tree/hld.cpp"

int main() {
    Scanner in;
    Printer out;
    ll a, b;
    in.read(a, b);
    out.println(a + b);
}
