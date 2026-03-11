#define PROBLEM "https://judge.yosupo.jp/problem/inverse_matrix"

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
#include "../math/inverse_matrix.cpp"

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

    auto B = inverse_matrix(A);
    if (B.empty()) {
        pr.writeln(-1);
        return 0;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            pr.write(B[i][j].val);
            pr.write(j + 1 == n ? '\n' : ' ');
        }
    }
    return 0;
}
