#define PROBLEM "https://judge.yosupo.jp/problem/counting_spanning_tree_directed"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
constexpr int MOD = 998244353;
#include "../util/fastio.cpp"
#include "../graph/spanning_tree/count_directed_spanning_trees.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int n, m, root;
    sc.read(n, m, root);
    vector<DirectedSpanningTreeEdge> edges(m);
    for (auto &edge : edges) sc.read(edge.from, edge.to);
    pr.println(count_directed_spanning_trees(n, root, edges).val);
}
