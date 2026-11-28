#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
#include "../util/fastio.cpp"
#include "../math/convolution/subset_convolution.cpp"
#include "../math/modular/modint_arbitrary.cpp"

namespace fixed_modint {
#include "../math/modular/modint_base.cpp"
}

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

void check_rank_products(int bits, int constant) {
    using M = fixed_modint::modint<998244353>;
    int size = 1 << bits;
    vector<M> a(size), b(size), expected(size);
    for (int rank = 0; rank <= bits; ++rank) {
        int prefix = (1 << rank) - 1;
        a[prefix] = rank == 0 ? constant : -1;
        b[prefix << (bits - rank)] = -1;
    }
    for (int i = 0; i <= bits; ++i) {
        int left = (1 << i) - 1;
        for (int j = 0; j + i <= bits; ++j) {
            int right = ((1 << j) - 1) << (bits - j);
            expected[left | right] += a[left] * b[right];
        }
    }
    assert(subset_convolution(a, b) == expected);
}

void self_check() {
    mt19937 rng(73);
    for (int bits = 0; bits <= 8; ++bits) {
        vector<int> a(1 << bits), b(1 << bits);
        for (int &x : a) x = -int(rng() % 256);
        for (int &x : b) x = -int(rng() % 256);
        using M = fixed_modint::modint<998244353>;
        using Other = fixed_modint::modint<1000000007>;
        check(vector<M>(a.begin(), a.end()), vector<M>(b.begin(), b.end()));
        check(vector<Other>(a.begin(), a.end()), vector<Other>(b.begin(), b.end()));
        for (unsigned mod : {6U, 998244353U}) {
            modint::set_mod(mod);
            check(vector<modint>(a.begin(), a.end()), vector<modint>(b.begin(), b.end()));
        }
    }
    for (int bits = 16; bits <= 18; ++bits) check_rank_products(bits, -1);
    check_rank_products(18, 18);
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
}
