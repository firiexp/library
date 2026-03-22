#define PROBLEM "https://judge.yosupo.jp/problem/subset_convolution"

#include <bits/stdc++.h>

static const int MOD = 998244353;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../util/modint.cpp"
#include "../math/subset_convolution.cpp"

int main() {
    Scanner sc;
    Printer pr;

    int n;
    sc.read(n);
    int m = 1 << n;
    vector<mint> a(m), b(m);
    for (int i = 0; i < m; ++i) {
        int x;
        sc.read(x);
        a[i] = x;
    }
    for (int i = 0; i < m; ++i) {
        int x;
        sc.read(x);
        b[i] = x;
    }
    auto c = subset_convolution(a, b);
    for (int i = 0; i < m; ++i) {
        if (i) pr.print(' ');
        pr.print(c[i].val);
    }
    pr.println();
    return 0;
}
