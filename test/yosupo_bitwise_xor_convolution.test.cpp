#define PROBLEM "https://judge.yosupo.jp/problem/bitwise_xor_convolution"

#include <vector>
using namespace std;

static const int MOD = 998244353;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../util/modint.cpp"
#include "../math/fwht.cpp"

int main() {
    Scanner sc;
    Printer pr;

    int n;
    sc.read(n);
    int sz = 1 << n;
    vector<mint> a(sz), b(sz), c(sz);
    for (int i = 0; i < sz; ++i) {
        int x;
        sc.read(x);
        a[i] = x;
    }
    for (int i = 0; i < sz; ++i) {
        int x;
        sc.read(x);
        b[i] = x;
    }
    fwht(a);
    fwht(b);
    for (int i = 0; i < sz; ++i) c[i] = a[i] * b[i];
    fwht(c);
    mint inv_sz = mint(1) / mint(sz);
    for (int i = 0; i < sz; ++i) {
        if (i) pr.print(' ');
        pr.print((c[i] * inv_sz).val);
    }
    pr.println();
    return 0;
}
