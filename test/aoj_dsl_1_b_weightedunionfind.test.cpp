#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/DSL_1_B"

#include <bits/stdc++.h>

using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../datastructure/weightedunionfind.cpp"

struct Group {
    using T = long long;
    static T op(T a, T b) { return a + b; }
    static T inv(T a) { return -a; }
    static T e() { return 0; }
};

int main() {
    Scanner sc;
    Printer pr;

    int n, q;
    sc.read(n, q);
    WeightedUnionFind<Group> uf(n);
    while (q--) {
        int t, x, y;
        long long z;
        sc.read(t, x, y);
        if (t == 0) {
            sc.read(z);
            uf.unite(x, y, z);
        } else {
            if (!uf.same(x, y)) pr.println('?');
            else pr.println(uf.diff(x, y));
        }
    }
    return 0;
}
