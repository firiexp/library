#define PROBLEM "https://judge.yosupo.jp/problem/matrix_rank"

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
#include "../math/gauss_jordan_mint.cpp"

int main() {
    Scanner sc;
    Printer pr;

    int n, m;
    sc.read(n, m);
    if (n == 0 || m == 0) {
        pr.println(0);
        return 0;
    }
    vector<vector<mint>> A(n, vector<mint>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int x;
            sc.read(x);
            A[i][j] = x;
        }
    }
    pr.println(gauss_jordan(A));
    return 0;
}
