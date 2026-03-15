#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_matrix"

#include <algorithm>
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

#include "../util/fastio.cpp"
#include "../math/squarematrix_mint.cpp"

using mat = SquareMatrixMint<200>;

static_assert(is_same_v<decltype(declval<mat::ar &>() *= declval<const mat &>()), mat::ar &>);

[[maybe_unused]] static void squarematrix_mint_api_smoke_test() {
    mat A;
    mat::PreparedMul prepared;
    mat::MatrixMulScratch matrix_scratch;
    mat::VecMulScratch vec_scratch;
    mat::ar x{};
    A.prepare_mul(prepared, 0);
    A.mul_assign_prepared(prepared, matrix_scratch, 0);
    A.mul_vec_assign_prepared(x, prepared, vec_scratch, 0);
}

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
            pr.write(B[i][j].val);
            pr.write(j + 1 == n ? '\n' : ' ');
        }
    }
    return 0;
}
