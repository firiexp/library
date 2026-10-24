#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
static const int MOD = 998244353;
#include "../util/modint.cpp"
#include "../math/gcd_transform.cpp"

template<class T>
void check(const vector<T> &a, const vector<T> &b) {
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
    auto x = a, y = b;
    gcd_transform(x);
    gcd_transform(y);
    for (int i = 0; i < n; ++i) x[i] *= y[i];
    gcd_itransform(x);
    vector<T> convolution(n);
    if (n) convolution[0] = a[0] * b[0];
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < n; ++j) convolution[gcd(i, j)] += a[i] * b[j];
    }
    assert(x == convolution);
}

int main() {
    mt19937 rng(269);
    for (int trial = 0; trial < 600; ++trial) {
        int n = trial < 100 ? trial : rng() % 100;
        vector<ll> a(n), b(n);
        for (auto &x : a) x = int(rng() % 21) - 10;
        for (auto &x : b) x = int(rng() % 21) - 10;
        check(a, b);
        check(vector<mint>(a.begin(), a.end()), vector<mint>(b.begin(), b.end()));
    }
}
