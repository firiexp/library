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

#include <charconv>
#include "../util/fastio.cpp"
#include "../math/linear_algebra/matrix_rank.cpp"

int main() {
    Scanner sc;
    Printer pr;

    int n, m;
    sc.read(n, m);
    vector<vector<mint>> A(n, vector<mint>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int x;
            sc.read(x);
            A[i][j] = x;
        }
    }
    pr.println(matrix_rank(std::move(A)));
    return 0;
}
