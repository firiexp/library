#ifndef FIRIEXP_LIBRARY_MATH_PRIME_TOTIENT_MOBIUS_SUM_CPP
#define FIRIEXP_LIBRARY_MATH_PRIME_TOTIENT_MOBIUS_SUM_CPP

#include "linear_sieve.cpp"
#include "../quotient_ranges.cpp"

class TotientMobiusSum {
    long long n;
    vector<long long> prefix_phi;
    vector<int> prefix_mobius;
    vector<pair<__int128, long long>> large;

public:
    TotientMobiusSum(long long n, int limit) : n(n) {
        assert(0 <= limit && limit <= n && limit < INT_MAX);
        assert(n / (limit + 1LL) <= limit);
        LinearSieve sieve(limit, false, true, true);
        prefix_phi.resize(limit + 1);
        prefix_mobius = std::move(sieve.mobius);
        for (int i = 1; i <= limit; ++i) {
            prefix_phi[i] = prefix_phi[i - 1] + sieve.phi[i];
            prefix_mobius[i] += prefix_mobius[i - 1];
        }

        int count = n / (limit + 1LL);
        large.resize(count + 1);
        for (int i = count; i >= 1; --i) {
            long long x = n / i;
            __int128 phi = (__int128)x * (x + 1) / 2, mobius = 1;
            for_each_quotient(x, [&](long long l, long long r, long long q) {
                auto [phi_q, mobius_q] = get(q);
                __int128 length = r - l + 1;
                phi -= length * phi_q;
                mobius -= length * mobius_q;
            }, 2);
            large[i] = {phi, (long long)mobius};
        }
    }

    pair<__int128, long long> get(long long x) const {
        assert(0 <= x && x <= n);
        if (x < (long long)prefix_phi.size()) return {prefix_phi[x], prefix_mobius[x]};
        long long i = n / x;
        assert(n / i == x);
        return large[i];
    }
};

#endif

/**
 * @brief オイラーのφ関数とメビウス関数の総和
 */
