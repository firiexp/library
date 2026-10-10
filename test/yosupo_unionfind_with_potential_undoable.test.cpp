#define PROBLEM "https://judge.yosupo.jp/problem/unionfind_with_potential"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../datastructure/undoable_weighted_unionfind.cpp"

struct Group {
    using T = int;
    static T op(T a, T b) { return a + b < 998244353 ? a + b : a + b - 998244353; }
    static T inv(T a) { return a ? 998244353 - a : 0; }
    static T e() { return 0; }
};

int main() {
    Scanner in;
    Printer out;
    int n, q;
    in.read(n, q);
    UndoableWeightedUnionFind<Group> uf(n);
    while (q--) {
        int type, u, v;
        in.read(type, u, v);
        if (type == 0) {
            int w;
            in.read(w);
            uf.unite(v, u, w);
            bool ok = uf.consistent();
            if (!ok) uf.undo();
            out.println(int(ok));
        } else {
            auto answer = uf.diff(v, u);
            out.println(answer ? *answer : -1);
        }
    }
}
