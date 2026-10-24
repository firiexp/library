#define PROBLEM "https://judge.yosupo.jp/problem/gcd_convolution"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
static const int MOD = 998244353;
#include "../util/fastio.cpp"
#include "../util/modint.cpp"
#include "../math/gcd_transform.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int n;
    sc.read(n);
    vector<mint> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; ++i) {
        int x;
        sc.read(x);
        a[i] = x;
    }
    for (int i = 1; i <= n; ++i) {
        int x;
        sc.read(x);
        b[i] = x;
    }
    gcd_transform(a);
    gcd_transform(b);
    for (int i = 1; i <= n; ++i) a[i] *= b[i];
    gcd_itransform(a);
    for (int i = 1; i <= n; ++i) {
        pr.print(a[i].val);
        pr.print(i == n ? '\n' : ' ');
    }
}
