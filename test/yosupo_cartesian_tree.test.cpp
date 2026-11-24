#define PROBLEM "https://judge.yosupo.jp/problem/cartesian_tree"

#include <bits/stdc++.h>

using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include <charconv>
#include "../util/fastio.cpp"
#include "../tree/cartesian_tree.cpp"

int main() {
    Scanner sc;
    Printer pr;

    int n;
    sc.read(n);
    vector<long long> a(n);
    for (auto &&x : a) sc.read(x);

    auto tree = cartesian_tree(a);
    tree.parent[tree.root] = tree.root;
    pr.println(tree.parent);
    return 0;
}
