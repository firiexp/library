#define STANDALONE

#include <bits/stdc++.h>

static const int MOD = 998244353;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
using namespace std;

template<class T> constexpr T INF = ::numeric_limits<T>::max() / 32 * 15 + 208;

#include "../util/modint.cpp"
#include "../math/berlekamp_massey.cpp"

#include "../util/fastio.cpp"

bool feasible(const vector<mint> &s, int degree) {
    int rows = (int)s.size() - degree;
    vector<vector<mint>> a(rows, vector<mint>(degree + 1));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < degree; ++j) a[i][j] = s[i + degree - j - 1];
        a[i][degree] = s[i + degree];
    }
    int rank = 0;
    for (int j = 0; j < degree && rank < rows; ++j) {
        int pivot = rank;
        while (pivot < rows && a[pivot][j] == mint(0)) ++pivot;
        if (pivot == rows) continue;
        swap(a[rank], a[pivot]);
        mint inv = mint(1) / a[rank][j];
        for (int k = j; k <= degree; ++k) a[rank][k] *= inv;
        for (int i = rank + 1; i < rows; ++i) {
            mint factor = a[i][j];
            for (int k = j; k <= degree; ++k) a[i][k] -= factor * a[rank][k];
        }
        ++rank;
    }
    for (int i = rank; i < rows; ++i) if (a[i][degree] != mint(0)) return false;
    return true;
}

void check(const vector<mint> &s) {
    auto c = berlekamp_massey(s);
    int degree = c.size();
    assert(degree <= (int)s.size());
    for (int n = degree; n < (int)s.size(); ++n) {
        mint expected = 0;
        for (int i = 0; i < degree; ++i) expected += c[i] * s[n - i - 1];
        assert(expected == s[n]);
    }
    assert(feasible(s, degree));
    for (int d = 0; d < degree; ++d) assert(!feasible(s, d));
}

void self_check() {
    mt19937 rng(182);
    for (int n = 0; n <= 24; ++n) {
        check(vector<mint>(n));
        vector<mint> geometric(n, 1), impulse(n);
        for (int i = 1; i < n; ++i) geometric[i] = geometric[i - 1] * mint(13);
        if (n) impulse[n / 2] = 1;
        check(geometric);
        check(impulse);
        for (int tc = 0; tc < 12; ++tc) {
            vector<mint> s(n);
            for (auto &x : s) x = rng() % (tc % 2 ? MOD : 3);
            check(s);
        }
    }
}

int main() {
    self_check();
}
