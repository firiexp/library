#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det"

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
#include "../math/matrix_determinant.cpp"

int main() {
    Scanner sc;
    Printer pr;

    int n;
    sc.read(n);
    vector<vector<mint>> A(n, vector<mint>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int x;
            sc.read(x);
            A[i][j] = x;
        }
    }
    pr.writeln(matrix_determinant(A).val);
    return 0;
}
