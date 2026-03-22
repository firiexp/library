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
        for (int i = 2; i <= this->n; ++i) {
            bool prime = min_factor.empty() ? prime_table[i] : min_factor[i] == 0;
            if (prime) {
                if (!min_factor.empty()) min_factor[i] = i;
                if (!phi.empty()) phi[i] = i - 1;
                if (!mobius.empty()) mobius[i] = -1;
                primes.emplace_back(i);
            }
            for (auto &&p : primes) {
                long long x = 1LL * i * p;
                if (x > this->n) break;
                if (!prime_table.empty()) prime_table[x] = false;
                if (!min_factor.empty()) min_factor[x] = p;
                bool same = i % p == 0;
                if (!phi.empty()) phi[x] = same ? phi[i] * p : phi[i] * (p - 1);
                if (!mobius.empty()) mobius[x] = same ? 0 : -mobius[i];
                if (same) break;
            }
        }
    }

    bool is_prime(int x) const {
        if (x < 2 || x > n) return false;
        if (!min_factor.empty()) return min_factor[x] == x;
        return prime_table[x];
    }
};

/**
 * @brief 線形篩(Linear Sieve)
 */

#endif
