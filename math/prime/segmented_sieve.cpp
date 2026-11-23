#ifndef FIRIEXP_LIBRARY_MATH_PRIME_SEGMENTED_SIEVE_CPP
#define FIRIEXP_LIBRARY_MATH_PRIME_SEGMENTED_SIEVE_CPP

#include "../isqrt.cpp"
#include "get_prime.cpp"

namespace segmented_sieve_detail {

template<class F>
void for_each_multiple(long long l, long long r, F visit) {
    if (l == r) return;
    auto limit = Isqrt(r - 1);
    assert(limit <= INT_MAX);
    for (long long p : get_prime(static_cast<int>(limit))) {
        long long first = max(p * p, (l + p - 1) / p * p);
        for (long long x = first; x < r; x += p) visit(x - l, p);
    }
}

}

vector<long long> segmented_primes(long long l, long long r) {
    assert(0 <= l && l <= r);
    vector<bool> composite(r - l);
    segmented_sieve_detail::for_each_multiple(l, r, [&](long long i, long long) {
        composite[i] = true;
    });
    vector<long long> primes;
    for (long long x = max(l, 2LL); x < r; ++x) {
        if (!composite[x - l]) primes.push_back(x);
    }
    return primes;
}

vector<vector<long long>> segmented_prime_factors(long long l, long long r) {
    assert(0 <= l && l <= r);
    vector<vector<long long>> factors(r - l);
    vector<long long> remaining(r - l);
    iota(remaining.begin(), remaining.end(), l);
    segmented_sieve_detail::for_each_multiple(l, r, [&](long long i, long long p) {
        do {
            factors[i].push_back(p);
            remaining[i] /= p;
        } while (remaining[i] % p == 0);
    });
    for (size_t i = 0; i < remaining.size(); ++i) {
        if (remaining[i] > 1) factors[i].push_back(remaining[i]);
    }
    return factors;
}

#endif

/**
 * @brief 区間篩による素数列挙と素因数分解
 */
