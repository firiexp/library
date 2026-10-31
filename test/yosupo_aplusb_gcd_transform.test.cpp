#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
static const int MOD = 998244353;
#include "../math/modular/modint.cpp"
#include "../math/convolution/gcd_transform.cpp"

template<class T>
void check_transform(const vector<T> &a) {
    int n = a.size();
    auto expected = a, inverse = a;
    for (int i = 1; i < n; ++i) {
        for (int j = 2 * i; j < n; j += i) expected[i] += a[j];
    }
    for (int i = n - 1; i > 0; --i) {
        for (int j = 2 * i; j < n; j += i) inverse[i] -= inverse[j];
    }
    auto actual = a;
    gcd_transform(actual);
    assert(actual == expected);
    gcd_itransform(actual);
    assert(actual == a);
    actual = a;
    gcd_itransform(actual);
    assert(actual == inverse);
    gcd_transform(actual);
    assert(actual == a);
}

template<class T>
void check(const vector<T> &a, const vector<T> &b) {
    check_transform(a);
    check_transform(b);
    auto original_a = a, original_b = b;
    vector<T> expected(max(a.size(), b.size()));
    for (int i = 1; i < (int)a.size(); ++i) {
        for (int j = 1; j < (int)b.size(); ++j) expected[gcd(i, j)] += a[i] * b[j];
    }
    assert(gcd_convolution(a, b) == expected);
    assert(a == original_a && b == original_b);
    assert(gcd_convolution(b, a) == expected);
    assert(gcd_convolution(move(original_a), move(original_b)) == expected);
}

int main() {
    for (int n = 0; n <= 3; ++n) {
        for (int m = 0; m <= 3; ++m) {
            check(vector<ll>(n, 7), vector<ll>(m, -3));
            check(vector<mint>(n, 7), vector<mint>(m, -3));
        }
    }
    mt19937 rng(269);
    for (int trial = 0; trial < 600; ++trial) {
        int n = trial < 100 ? trial : rng() % 100;
        int m = trial % 3 == 0 ? n : rng() % 100;
        vector<ll> a(n), b(m);
        for (auto &x : a) x = int(rng() % 21) - 10;
        for (auto &x : b) x = int(rng() % 21) - 10;
        check(a, b);
        check(vector<mint>(a.begin(), a.end()), vector<mint>(b.begin(), b.end()));
    }
}
