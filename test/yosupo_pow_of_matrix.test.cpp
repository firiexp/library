#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_matrix"

#include <algorithm>
#include <cassert>
#include <array>
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
#include <utility>

#include <charconv>
#include "../util/fastio.cpp"
#include "../math/squarematrix_mint.cpp"

using mat = SquareMatrixMint<200>;

int main() {
    Scanner sc;
    Printer pr;

    int n;
    ll k;
    sc.read(n, k);
    mat A;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int x;
            sc.read(x);
            A[i][j] = x;
        }
    }

    auto B = A.pow(k, n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            pr.print(B[i][j].val);
            pr.print(j + 1 == n ? '\n' : ' ');
        }
    }
    return 0;
}
