#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using uint = unsigned;
constexpr int MOD = 998244353;
#include "../util/fastio.cpp"
#include "../math/linear_algebra/inverse_matrix.cpp"

bool nonsingular(vector<vector<mint>> a) {
    int n = (int)a.size();
    for (int col = 0; col < n; ++col) {
        int pivot = col;
        while (pivot < n && a[pivot][col] == mint(0)) ++pivot;
        if (pivot == n) return false;
        swap(a[col], a[pivot]);
        for (int row = col + 1; row < n; ++row) {
            mint factor = a[row][col] / a[col][col];
            for (int j = col + 1; j < n; ++j) a[row][j] -= factor * a[col][j];
        }
    }
    return true;
}

void check(const vector<vector<mint>>& a) {
    auto original = a;
    auto b = inverse_matrix(a);
    assert(a == original);
    int n = (int)a.size();
    if (n == 0) {
        assert(b.empty());
        return;
    }
    assert(!b.empty() == nonsingular(a));
    if (b.empty()) return;
    assert((int)b.size() == n);
    for (const auto& row : b) assert((int)row.size() == n);
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
        mint left = 0, right = 0;
        for (int k = 0; k < n; ++k) {
            left += a[i][k] * b[k][j];
            right += b[i][k] * a[k][j];
        }
        assert(left == mint(i == j) && right == mint(i == j));
    }
}

int main() {
    check({});
    check({{0}});
    check({{7}});
    for (int mask = 0; mask < 512; ++mask) {
        vector<vector<mint>> a(3, vector<mint>(3));
        for (int i = 0; i < 9; ++i) a[i / 3][i % 3] = mask >> i & 1;
        check(a);
    }
    mt19937 rng(169);
    for (int n = 1; n <= 12; ++n) {
        vector<vector<mint>> a(n, vector<mint>(n));
        vector<int> permutation(n);
        iota(permutation.begin(), permutation.end(), 0);
        for (int tc = 0; tc < 100; ++tc) {
            for (auto& row : a) for (auto& x : row) x = rng();
            check(a);
            if (n > 1) {
                a[n - 1] = a[0];
                check(a);
            }
            for (int i = 0; i < n; ++i) for (int j = 0; j < i; ++j) a[i][j] = 0;
            check(a);
            for (auto& row : a) fill(row.begin(), row.end(), mint(0));
            shuffle(permutation.begin(), permutation.end(), rng);
            for (int i = 0; i < n; ++i) a[i][permutation[i]] = 1 + rng() % (MOD - 1);
            check(a);
        }
    }
}
