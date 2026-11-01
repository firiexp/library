#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

#include "../math/prime/divisor.cpp"
#include "../math/prime/primefactor_ll.cpp"

template<class T>
void check_large(T n, const vector<T> &factors) {
    auto ds = divisor_from_factors(factors);
    size_t count = 1;
    __uint128_t product = 1;
    for (size_t i = 0; i < factors.size();) {
        size_t j = i;
        while (j < factors.size() && factors[j] == factors[i]) {
            product *= factors[j++];
        }
        count *= j - i + 1;
        i = j;
    }
    assert(product == (__uint128_t)n);
    assert(ds.size() == count);
    assert(ds.front() == 1 && ds.back() == n);
    for (size_t i = 0; i < ds.size(); ++i) {
        assert(n % ds[i] == 0);
        assert(i == 0 || ds[i - 1] < ds[i]);
        assert((__uint128_t)ds[i] * ds[ds.size() - 1 - i] == (__uint128_t)n);
    }
}

int main() {
    assert(divisor_from_factors(vector<int>{}) == vector<int>{1});
    for (int n = 1; n <= 5000; ++n) {
        vector<int> expected;
        for (int d = 1; d <= n; ++d) {
            if (n % d == 0) expected.push_back(d);
        }
        assert(divisor_from_factors(prime_factor(n)) == expected);
    }
    for (ll n : {1LL, 1000000007LL, 1000000000000LL, 1LL << 62,
                 1000000007LL * 1000000009LL, LLONG_MAX}) {
        check_large(n, prime_factor(n));
    }
    check_large(1ULL << 63, vector<ull>(63, 2));
    check_large(ULLONG_MAX, vector<ull>{3, 5, 17, 257, 641, 65537, 6700417});
}
