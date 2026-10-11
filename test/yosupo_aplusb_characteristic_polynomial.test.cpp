#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using uint = unsigned;
#include "../util/fastio.cpp"
#include "../util/modint_base.cpp"
#include "../math/characteristic_polynomial.cpp"

template<class T>
vector<T> determinant_polynomial(const vector<vector<T>>& a) {
    int n = (int)a.size();
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 0);
    vector<T> result(n + 1);
    do {
        int inversions = 0;
        for (int i = 0; i < n; ++i) for (int j = 0; j < i; ++j)
            inversions += perm[j] > perm[i];
        vector<T> term = {T(inversions % 2 ? -1 : 1)};
        for (int i = 0; i < n; ++i) {
            vector<T> next(term.size() + 1);
            for (int j = 0; j < (int)term.size(); ++j) {
                next[j] -= a[i][perm[i]] * term[j];
                if (perm[i] == i) next[j + 1] += term[j];
            }
            term = std::move(next);
        }
        for (int j = 0; j <= n; ++j) result[j] += term[j];
    } while (next_permutation(perm.begin(), perm.end()));
    return result;
}

template<class T>
void check(const vector<vector<T>>& a) {
    auto original = a;
    auto p = characteristic_polynomial(a);
    assert(a == original);
    assert(p == determinant_polynomial(a));
    assert(p.size() == a.size() + 1 && p.back() == T(1));
    if (!a.empty()) {
        T trace = 0;
        for (int i = 0; i < (int)a.size(); ++i) trace += a[i][i];
        assert(p[a.size() - 1] == -trace);
    }
}

template<unsigned Mod>
void check_field() {
    using T = modint<Mod>;
    check<T>({});
    check<T>({{1, 2}, {3, 4}});
    assert(characteristic_polynomial<T>({{1, 2}, {3, 4}}) == vector<T>({-2, -5, 1}));
    check<T>({{0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}, {1, 0, 0, 0}});
    mt19937 rng(Mod);
    for (int n = 0; n <= 6; ++n) {
        vector<vector<T>> a(n, vector<T>(n));
        check(a);
        for (int i = 0; i < n; ++i) a[i][i] = 1;
        check(a);
        for (int i = 0; i + 1 < n; ++i) a[i][i + 1] = 1;
        check(a);
        for (int tc = 0; tc < 70; ++tc) {
            for (auto& row : a) for (auto& x : row) x = rng();
            check(a);
        }
    }
    vector<vector<T>> triangle(30, vector<T>(30));
    vector<T> expected = {T(1)};
    for (int i = 0; i < 30; ++i) {
        for (int j = i; j < 30; ++j) triangle[i][j] = rng();
        vector<T> next(expected.size() + 1);
        for (int j = 0; j < (int)expected.size(); ++j) {
            next[j + 1] += expected[j];
            next[j] -= triangle[i][i] * expected[j];
        }
        expected = std::move(next);
    }
    assert(characteristic_polynomial(triangle) == expected);
    for (int i = 0; i < 30; ++i) for (int j = 0; j < i; ++j)
        swap(triangle[i][j], triangle[j][i]);
    assert(characteristic_polynomial(triangle) == expected);
}

int main() {
    check_field<2>();
    check_field<3>();
    check_field<5>();
    check_field<998244353>();
    for (int mask = 0; mask < 512; ++mask) {
        vector<vector<modint<2>>> a(3, vector<modint<2>>(3));
        for (int i = 0; i < 9; ++i) a[i / 3][i % 3] = mask >> i & 1;
        check(a);
    }
    Scanner sc;
    Printer pr;
    long long a, b;
    sc.read(a, b);
    pr.println(a + b);
}
