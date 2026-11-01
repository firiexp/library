#define PROBLEM "https://judge.yosupo.jp/problem/counting_spanning_tree_undirected"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
constexpr int MOD = 998244353;
#include "../util/fastio.cpp"
#include "../graph/spanning_tree/count_spanning_trees.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int n, m;
    sc.read(n, m);
    vector<SpanningTreeEdge> edges(m);
    for (auto &edge : edges) sc.read(edge.u, edge.v);
    pr.println(count_spanning_trees(n, edges).val);
}
