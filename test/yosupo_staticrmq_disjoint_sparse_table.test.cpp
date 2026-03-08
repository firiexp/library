#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include <algorithm>
#include <vector>
using namespace std;

#include "../util/fastio.cpp"
#include "../datastructure/disjoint_sparse_table.cpp"

struct F {
    using T = int;
    static T f(T a, T b) { return min(a, b); }
    static T e() { return 1 << 30; }
};

int main() {
    Scanner sc;
    Printer pr;
    int n, q;
    sc.read(n, q);
    vector<int> a(n);
    for (auto &&x : a) sc.read(x);

    DisjointSparseTable<F> dst(a);
    while (q--) {
        int l, r;
        sc.read(l, r);
        pr.writeln(dst.query(l, r));
    }
    return 0;
}
