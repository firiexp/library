#ifndef FIRIEXP_LIBRARY_MATH_LINEAR_SIEVE_CPP
#define FIRIEXP_LIBRARY_MATH_LINEAR_SIEVE_CPP

struct LinearSieve {
    int n;
    vector<int> primes;
    vector<int> min_factor;
    vector<int> phi;
    vector<int> mobius;
    vector<bool> prime_table;

    explicit LinearSieve(int n, bool need_min_factor = false, bool need_phi = false, bool need_mobius = false)
        : n(n < 0 ? 0 : n),
          min_factor(need_min_factor ? this->n + 1 : 0),
          phi(need_phi ? this->n + 1 : 0),
          mobius(need_mobius ? this->n + 1 : 0),
          prime_table(need_min_factor ? 0 : this->n + 1, true) {
        if (!prime_table.empty()) {
            prime_table[0] = false;
            if (this->n >= 1) prime_table[1] = false;
        }
        if (!min_factor.empty() && this->n >= 1) min_factor[1] = 1;
        if (!phi.empty()) {
            phi[0] = 0;
            if (this->n >= 1) phi[1] = 1;
        }
        if (!mobius.empty()) {
            mobius[0] = 0;
            if (this->n >= 1) mobius[1] = 1;
        }
        if (need_min_factor) {
            if (need_phi) {
                if (need_mobius) build<true, true, true>();
                else build<true, true, false>();
            } else {
                if (need_mobius) build<true, false, true>();
                else build<true, false, false>();
            }
        } else {
            if (need_phi) {
                if (need_mobius) build<false, true, true>();
                else build<false, true, false>();
            } else {
                if (need_mobius) build<false, false, true>();
                else build<false, false, false>();
            }
        }
    }

    bool is_prime(int x) const {
        if (x < 2 || x > n) return false;
        if (!min_factor.empty()) return min_factor[x] == x;
        return prime_table[x];
    }

private:
    template<bool NeedMinFactor, bool NeedPhi, bool NeedMobius>
    void build() {
        for (int i = 2; i <= n; ++i) {
            bool prime = NeedMinFactor ? min_factor[i] == 0 : prime_table[i];
            if (prime) {
                if constexpr (NeedMinFactor) min_factor[i] = i;
                if constexpr (NeedPhi) phi[i] = i - 1;
                if constexpr (NeedMobius) mobius[i] = -1;
                primes.emplace_back(i);
            }
            for (auto &&p : primes) {
                long long x = 1LL * i * p;
                if (x > n) break;
                if constexpr (NeedMinFactor) min_factor[x] = p;
                else prime_table[x] = false;
                bool same = NeedMinFactor ? p == min_factor[i] : i % p == 0;
                if constexpr (NeedPhi) phi[x] = same ? phi[i] * p : phi[i] * (p - 1);
                if constexpr (NeedMobius) mobius[x] = same ? 0 : -mobius[i];
                if (same) break;
            }
        }
    }
};

/**
 * @brief 線形篩(Linear Sieve)
 */

#endif
