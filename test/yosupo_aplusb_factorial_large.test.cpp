#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
const int MOD = 998244353;

#include "../math/factorial.cpp"
#include "../util/biginteger.cpp"

template <uint P>
void check() {
    using Mint = modint<P>;
    const Factorial<Mint> factorial;
    assert(factorial.large_C(-1, 0) == Mint(0));
    assert(factorial.large_C(5, -1) == Mint(0));
    assert(factorial.large_C(5, 6) == Mint(0));
    assert(factorial.large_C(LLONG_MIN, LLONG_MIN) == Mint(0));
    assert(factorial.large_C(LLONG_MAX, LLONG_MIN) == Mint(0));
    assert(factorial.max_n() == 0);
    assert(factorial.large_C(2LL * P, 1) == Mint(0));
    assert(factorial.max_n() == 0);
    mt19937_64 random(270);
    vector<ll> values = {0, 1, P - 1, P, P + 1LL, 2LL * P - 1, 2LL * P,
                        2LL * P + 1, LLONG_MAX, LLONG_MAX - 1, 1000000000000000000LL};
    for (int n = 0; n <= 150; ++n) values.push_back(n);
    for (int tc = 0; tc < 500; ++tc) values.push_back(random() & LLONG_MAX);
    int limit = min(60U, P - 1);
    for (ll n : values) {
        BigInteger value = 1;
        for (int k = 0; k <= min<ll>(n, limit); ++k) {
            if (k) value = value * (n - k + 1) / k;
            Mint expected(stoll((value % P).to_string()));
            assert(factorial.large_C(n, k) == expected);
            assert(factorial.large_C(n, n - k) == expected);
            assert(factorial.max_n() <= limit);
        }
    }
    int before = factorial.max_n();
    const Factorial<Mint> shared;
    assert(shared.max_n() == before);
    int small_limit = min(150U, P - 1);
    for (int n = 0; n <= small_limit; ++n) {
        for (int k = 0; k <= n; ++k) {
            assert(factorial.large_C(n, k) == factorial.C(n, k));
        }
    }
    assert(shared.max_n() == max(before, small_limit));
}

int main() {
    check<2>();
    check<3>();
    check<5>();
    check<17>();
    check<998244353>();
    check<1000000007>();
}
