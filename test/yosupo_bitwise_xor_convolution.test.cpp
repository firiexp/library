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

#include <charconv>
#include "../util/fastio.cpp"
#include "../util/modint.cpp"
#include "../math/fwht.cpp"

int main() {
    Scanner sc;
    Printer pr;

    int n;
    sc.read(n);
    int sz = 1 << n;
    vector<mint> a(sz), b(sz);
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
    auto c = xor_convolution(std::move(a), std::move(b));
    for (int i = 0; i < sz; ++i) {
        if (i) pr.print(' ');
        pr.print(c[i].val);
    }
    pr.println();
    return 0;
}
