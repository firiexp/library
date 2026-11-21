long long mod_sqrt(long long a, long long p) {
    a %= p;
    if (a < 0) a += p;
    if (a == 0 || p == 2) return a;

    auto multiply = [p](long long x, long long y) -> long long {
        return (unsigned __int128)x * y % p;
    };
    auto power = [&](long long base, long long exponent) {
        long long result = 1;
        while (exponent) {
            if (exponent & 1) result = multiply(result, base);
            base = multiply(base, base);
            exponent >>= 1;
        }
        return result;
    };
    if (p % 4 == 3) {
        long long root = power(a, p / 4 + 1);
        return multiply(root, root) == a ? root : -1;
    }
    if (power(a, (p - 1) / 2) != 1) return -1;

    struct Parameters {
        long long p = 0, q = 0, c = 0;
        int s = 0;
    };
    static thread_local Parameters cache;
    if (cache.p != p) {
        long long q = p - 1;
        int s = 0;
        while ((q & 1) == 0) {
            ++s;
            q >>= 1;
        }
        long long z = 2;
        while (power(z, (p - 1) / 2) == 1) {
            static thread_local std::mt19937_64 rng(std::random_device{}());
            z = std::uniform_int_distribution<long long>(2, p - 1)(rng);
        }
        cache = {p, q, power(z, q), s};
    }
    long long q = cache.q, c = cache.c;
    long long t = power(a, q);
    long long r = power(a, (q + 1) / 2);
    int m = cache.s;
    while (t != 1) {
        int i = 1;
        long long tt = multiply(t, t);
        while (i < m && tt != 1) {
            tt = multiply(tt, tt);
            ++i;
        }
        long long b = c;
        for (int j = i + 1; j < m; ++j) b = multiply(b, b);
        r = multiply(r, b);
        c = multiply(b, b);
        t = multiply(t, c);
        m = i;
    }
    return r;
}

/**
 * @brief 平方根(mod p)
 */
