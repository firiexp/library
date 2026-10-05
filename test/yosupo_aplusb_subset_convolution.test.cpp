#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include "../util/fastio.cpp"
#include "../math/subset_convolution.cpp"

struct Matrix {
    array<int, 4> a{};
    Matrix(int x = 0) : a{x, 0, 0, x} {}
    Matrix &operator+=(const Matrix &other) {
        for (int i = 0; i < 4; ++i) a[i] = (a[i] + other.a[i]) % 17;
        return *this;
    }
    Matrix &operator-=(const Matrix &other) {
        for (int i = 0; i < 4; ++i) a[i] = (a[i] + 17 - other.a[i]) % 17;
        return *this;
    }
    Matrix operator*(const Matrix &other) const {
        Matrix result;
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                for (int k = 0; k < 2; ++k) {
                    result.a[2 * i + j] += a[2 * i + k] * other.a[2 * k + j];
                }
                result.a[2 * i + j] %= 17;
            }
        }
        return result;
    }
    bool operator==(const Matrix &other) const { return a == other.a; }
};

template<class T>
void check(const vector<T> &a, const vector<T> &b) {
    auto original_a = a, original_b = b;
    int n = 1;
    while (n < (int)max(a.size(), b.size())) n *= 2;
    vector<T> expected(n);
    for (int mask = 0; mask < n; ++mask) {
        for (int sub = mask;; sub = (sub - 1) & mask) {
            if (sub < (int)a.size() && (mask ^ sub) < (int)b.size()) {
                expected[mask] += a[sub] * b[mask ^ sub];
            }
            if (sub == 0) break;
        }
    }
    assert(subset_convolution(a, b) == expected);
    assert(a == original_a && b == original_b);
}

void self_check() {
    mt19937 rng(73);
    for (int n = 0; n <= 20; ++n) {
        for (int m = 0; m <= 20; ++m) {
            check(vector<ll>(n), vector<ll>(m, 1));
            check(vector<Matrix>(n), vector<Matrix>(m, 1));
        }
    }
    for (int tc = 0; tc < 2000; ++tc) {
        vector<ll> a(rng() % 129), b(rng() % 129);
        for (auto &x : a) x = (int)(rng() % 7) - 3;
        for (auto &x : b) x = (int)(rng() % 7) - 3;
        check(a, b);
        check(a, a);
    }
    Matrix x, y;
    x.a = {0, 1, 0, 0};
    y.a = {0, 0, 1, 0};
    assert(!((x * y) == (y * x)));
    check(vector<Matrix>{x}, vector<Matrix>{y});
    for (int tc = 0; tc < 1000; ++tc) {
        vector<Matrix> a(rng() % 65), b(rng() % 65);
        for (auto &mat : a) for (auto &v : mat.a) v = rng() % 17;
        for (auto &mat : b) for (auto &v : mat.a) v = rng() % 17;
        check(a, b);
        check(a, a);
    }
}

int main() {
    self_check();
    Scanner sc;
    Printer pr;
    ll a, b;
    sc.read(a, b);
    pr.println(a + b);
}
