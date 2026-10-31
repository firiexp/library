#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_tree_subtree_add_subtree_sum"
#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../tree/dynamic_tree/euler_tour_tree.cpp"

int main() {
    Scanner in;
    Printer out;
    int n, q;
    in.read(n, q);
    vector<long long> values(n);
    in.read(values);
    EulerTourTree tree(values);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        in.read(u, v);
        tree.link(u, v);
    }
    while (q--) {
        int type;
        in.read(type);
        if (type == 0) {
            int u, v, w, x;
            in.read(u, v, w, x);
            tree.cut(u, v);
            tree.link(w, x);
        } else if (type == 1) {
            int v, p;
            long long x;
            in.read(v, p, x);
            tree.subtree_add(v, p, x);
        } else {
            int v, p;
            in.read(v, p);
            out.println(tree.subtree_sum(v, p));
        }
    }
}
