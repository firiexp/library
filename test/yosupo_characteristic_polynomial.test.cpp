#define PROBLEM "https://judge.yosupo.jp/problem/characteristic_polynomial"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using uint = unsigned;
constexpr int MOD = 998244353;
#include "../util/fastio.cpp"
#include "../math/modular/modint.cpp"
#include "../math/linear_algebra/characteristic_polynomial.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int n;
    sc.read(n);
    vector<vector<mint>> a(n, vector<mint>(n));
    for (auto& row : a) for (auto& x : row) {
        int value;
        sc.read(value);
        x = value;
    }
    auto p = characteristic_polynomial(std::move(a));
    for (int i = 0; i <= n; ++i) {
        if (i) pr.print(' ');
        pr.print(p[i].val);
    }
    pr.println();
}
