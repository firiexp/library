#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_matrix"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
static const int MOD = 998244353;
#include "../util/fastio.cpp"
#include "../util/modint.cpp"
#include "../math/matrix.cpp"
#include "../math/squarematrix.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int n;
    ll k;
    sc.read(n, k);
    matrix<SemiRing> a(n);
    SquareMatrix<SemiRing, 200> fixed;
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
        int x;
        sc.read(x);
        fixed[i][j] = a[i][j] = x;
    }
    auto b = a.pow(k);
    auto fixed_power = fixed.pow(k, n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            assert(b[i][j] == fixed_power[i][j]);
            pr.print(b[i][j].val);
            pr.print(j + 1 == n ? '\n' : ' ');
        }
    }
}
