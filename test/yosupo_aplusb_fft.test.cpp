#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;
constexpr int MOD = 1000000007;

#include "../util/fastio.cpp"
#include "../math/fft.cpp"

vector<uint> naive(const vector<uint> &a, const vector<uint> &b) {
    if (a.empty() || b.empty()) return {};
    vector<uint> result(a.size() + b.size() - 1);
    for (size_t k = 0; k < result.size(); ++k) {
        __uint128_t sum = 0;
        for (size_t i = 0; i < a.size(); ++i) {
            if (i <= k && k - i < b.size()) sum += (__uint128_t)a[i] * b[k - i];
        }
        result[k] = sum % MOD;
    }
    return result;
}

void check(const vector<uint> &a, const vector<uint> &b) {
    auto expected = naive(a, b);
    assert(ArbitraryConvolution::convolution_mod(a, b) == expected);
    assert(ArbitraryConvolution::convolution_mod(b, a) == expected);
    poly p{vector<mint>(a.begin(), a.end())}, q{vector<mint>(b.begin(), b.end())};
    const auto original_p = p.v, original_q = q.v;
    auto compare = [&](const poly &value) {
        assert(value.size() == int(expected.size()));
        for (int i = 0; i < value.size(); ++i) assert(value[i].val == expected[i]);
    };
    compare(p * q);
    compare(q * p);
    assert(p.v == original_p && q.v == original_q);
    p *= q;
    compare(p);
    assert(q.v == original_q);
}

void self_check() {
    mt19937 rng(216);
    auto random_vector = [&](int n) {
        vector<uint> values(n);
        for (uint &x : values) x = rng();
        return values;
    };
    for (int n = 0; n <= 20; ++n)
        for (int m = 0; m <= 20; ++m) check(random_vector(n), random_vector(m));
    for (int n : {1, 2, 127, 128, 129, 255, 256, 257, 511, 512, 513}) {
        auto a = random_vector(n);
        auto expected = naive(a, a);
        poly p{vector<mint>(a.begin(), a.end())};
        p *= p;
        assert(p.size() == int(expected.size()));
        for (int i = 0; i < p.size(); ++i) assert(p[i].val == expected[i]);
        assert(ArbitraryConvolution::convolution_mod(a, a) == expected);
        for (int m : {0, 1, 2, 127, 128, 129}) check(a, random_vector(m));
    }
    for (int total : {255, 256, 257, 511, 512, 513, 1023, 1024, 1025}) {
        int n = total / 2, m = total - n + 1;
        check(random_vector(n), random_vector(m));
        check(vector<uint>(n, MOD - 1), vector<uint>(m, MOD - 1));
    }
    check(vector<uint>(513, 0), vector<uint>(128, UINT_MAX));
    check(vector<uint>(129, UINT_MAX), vector<uint>(129, UINT_MAX));
    check(vector<uint>(513, 0), vector<uint>{0});
    check(vector<uint>{1}, random_vector(513));
    poly empty;
    empty *= empty;
    assert(empty.size() == 0);
}

int main() {
    self_check();
}
