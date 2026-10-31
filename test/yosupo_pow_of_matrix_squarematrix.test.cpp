#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_matrix"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
static const int MOD = 998244353;
#include "../util/fastio.cpp"
#include "../math/modular/modint.cpp"
#include "../math/linear_algebra/squarematrix.cpp"

struct SemiRing {
    using T = mint;
    static T zero() { return 0; }
    static T one() { return 1; }
    static T mul(T a, T b) { return a * b; }
    static void add(T &a, T b) { a += b; }
};

int main() {
    Scanner sc;
    Printer pr;
    int n;
    ll k;
    sc.read(n, k);
    SquareMatrix<SemiRing, 200> a;
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
        int x;
        sc.read(x);
        a[i][j] = x;
    }
    auto b = a.pow(k, n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            pr.print(b[i][j].val);
            pr.print(j + 1 == n ? '\n' : ' ');
        }
    }
}
