#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"

#include <bits/stdc++.h>

static const int MOD = 1000000007;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
using namespace std;

#include "../util/fastio.cpp"
#include "../math/fft.cpp"

int main() {
    Scanner sc;
    Printer pr;

    int n, m;
    sc.read(n, m);
    poly a(n), b(m);
    for (int i = 0; i < n; ++i) {
        int x;
        sc.read(x);
        a[i] = x;
    }
    for (int i = 0; i < m; ++i) {
        int x;
        sc.read(x);
        b[i] = x;
    }
    a *= b;
    for (int i = 0; i < n + m - 1; ++i) {
        if (i) pr.write(' ');
        pr.write(a[i].val);
    }
    pr.writeln();
    return 0;
}
