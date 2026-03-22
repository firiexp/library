#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include <bits/stdc++.h>

using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../datastructure/sparsetable.cpp"

struct F {
    using T = int;
    static T f(T a, T b) { return min(a, b); }
};

int main() {
    Scanner sc;
    Printer pr;

    int n, q;
    sc.read(n, q);
    vector<int> a(n);
    for (auto &&x : a) sc.read(x);

    SparseTable<F> st(a);
    while (q--) {
        int l, r;
        sc.read(l, r);
        pr.println(st.query(l, r));
    }
    return 0;
}
