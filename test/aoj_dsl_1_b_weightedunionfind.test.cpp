#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/DSL_1_B"

#include <bits/stdc++.h>

using namespace std;

#include "../util/fastio.cpp"
#include "../datastructure/weightedunionfind.cpp"

int main() {
    Scanner sc;
    Printer pr;

    int n, q;
    sc.read(n, q);
    WeightedUnionFind<long long> uf(n);
    while (q--) {
        int t, x, y;
        long long z;
        sc.read(t, x, y);
        if (t == 0) {
            sc.read(z);
            uf.unite(x, y, z);
        } else {
            if (!uf.same(x, y)) pr.writeln('?');
            else pr.writeln(uf.diff(x, y));
        }
    }
    return 0;
}
