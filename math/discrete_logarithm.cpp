#include <cmath>
#include <limits>
#include <numeric>
#include <unordered_map>

long long discrete_logarithm_mul(long long a, long long b, long long mod) {
    using i128 = __int128_t;
    return (long long)((i128)a * b % mod);
}

long long discrete_logarithm(long long x, long long y, long long mod) {
    if (mod == 1) return 0;
    x %= mod;
    y %= mod;
    if (x < 0) x += mod;
    if (y < 0) y += mod;
    if (y == 1) return 0;

    long long add = 0;
    long long k = 1 % mod;
    while (true) {
        long long g = std::gcd(x, mod);
        if (g == 1) break;
        if (y == k) return add;
        if (y % g != 0) return -1;
        y /= g;
        mod /= g;
        ++add;
        k = discrete_logarithm_mul(k, x / g, mod);
    }

    long long n = (long long)std::sqrt((long double)mod) + 1;
    std::unordered_map<long long, long long> baby;
    baby.reserve((size_t)n * 2 + 1);

    long long giant = 1;
    for (long long i = 0; i < n; ++i) {
        giant = discrete_logarithm_mul(giant, x, mod);
    }

    long long cur = k;
    for (long long p = 1; p <= n; ++p) {
        cur = discrete_logarithm_mul(cur, giant, mod);
        if (!baby.count(cur)) baby[cur] = p;
    }

    long long ans = std::numeric_limits<long long>::max();
    cur = y;
    for (long long q = 0; q <= n; ++q) {
        auto it = baby.find(cur);
        if (it != baby.end()) {
            long long cand = it->second * n - q + add;
            if (cand < ans) ans = cand;
        }
        cur = discrete_logarithm_mul(cur, x, mod);
    }
    return ans == std::numeric_limits<long long>::max() ? -1 : ans;
}

/**
 * @brief 離散対数(Discrete Logarithm)
 */
