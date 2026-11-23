#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;

#include "../math/isqrt.cpp"
#include "../math/prime/primefactor_ll.cpp"
#include "../math/prime/segmented_sieve.cpp"

void check_interval(long long l, long long r) {
    auto factors = segmented_prime_factors(l, r);
    assert(factors.size() == size_t(r - l));
    vector<long long> primes;
    for (long long x = l; x < r; ++x) {
        if (miller_rabin(x)) primes.push_back(x);
        if (x == 0) assert(factors[x - l].empty());
        else assert(factors[x - l] == prime_factor(x));
    }
    assert(segmented_primes(l, r) == primes);
}

int main() {
    for (int l = 0; l <= 32; ++l) {
        for (int r = l; r <= 32; ++r) check_interval(l, r);
    }
    check_interval(0, 513);
    constexpr long long square = 999983LL * 999983;
    check_interval(square - 1, square);
    check_interval(square, square + 1);
    constexpr long long trillion = 1000000000000LL;
    check_interval(trillion, trillion + 20000);
    check_interval(100 * trillion - 64, 100 * trillion);
}
