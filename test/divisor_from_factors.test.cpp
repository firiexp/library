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
    vector<T> expected{n};
    __uint128_t product = 1;
    for (size_t i = 0; i < factors.size();) {
        T p = factors[i];
        size_t size = expected.size();
        for (size_t j = 0; j < size; ++j) {
            T d = expected[j];
            while (d % p == 0) {
                d /= p;
                expected.push_back(d);
            }
        }
        do {
            product *= p;
            ++i;
        } while (i < factors.size() && factors[i] == p);
    }
    assert(product == (__uint128_t)n);
    sort(expected.begin(), expected.end());
    assert(ds == expected);
    assert(ds.front() == 1 && ds.back() == n);
    for (size_t i = 0; i < ds.size(); ++i) {
        assert(n % ds[i] == 0);
        assert(i == 0 || ds[i - 1] < ds[i]);
        assert((__uint128_t)ds[i] * ds[ds.size() - 1 - i] == (__uint128_t)n);
    }
}

int main() {
    assert(divisor_from_factors(vector<int>{}) == vector<int>{1});
    const int limit = 10000;
    vector<vector<int>> expected(limit + 1);
    for (int d = 1; d <= limit; ++d) {
        for (int n = d; n <= limit; n += d) expected[n].push_back(d);
    }
    for (int n = 1; n <= limit; ++n) {
        assert(divisor_from_factors(prime_factor(n)) == expected[n]);
    }
    for (ll n : {1LL, 1000000007LL, 1000000000000LL, 1LL << 62, 1LL << 60,
                 360360LL, 614889782588491410LL, 897612484786617600LL,
                 9200527969062830400LL, 2 * 4052555153018976267LL,
                 1000000007LL * 1000000009LL, LLONG_MAX}) {
        check_large(n, prime_factor(n));
    }
    check_large(UINT_MAX, vector<unsigned>{3, 5, 17, 257, 65537});
    check_large(1ULL << 63, vector<ull>(63, 2));
    check_large(ULLONG_MAX, vector<ull>{3, 5, 17, 257, 641, 65537, 6700417});
    check_large(18446744073709551557ULL, vector<ull>{18446744073709551557ULL});
}
