#define PROBLEM "https://judge.yosupo.jp/problem/matrix_product"

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
#include "../math/matrix.cpp"

int main() {
    Scanner sc;
    Printer pr;

    int n, m, k;
    sc.read(n, m, k);
    if (n == 0 || m == 0 || k == 0) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < k; ++j) {
                pr.print(0);
                pr.print(j + 1 == k ? '\n' : ' ');
            }
            if (k == 0) pr.print('\n');
        }
        return 0;
    }
    matrix<SemiRing> A(n, m), B(m, k);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int x;
            sc.read(x);
            A[i][j] = x;
        }
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < k; ++j) {
            int x;
            sc.read(x);
            B[i][j] = x;
        }
    }

    auto C = A * B;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            pr.print(C[i][j].val);
            pr.print(j + 1 == k ? '\n' : ' ');
        }
    }
    return 0;
}
