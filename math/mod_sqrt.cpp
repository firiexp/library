long long mod_pow(long long a, long long n, long long mod) {
    long long r = 1;
    while (n) {
        if (n & 1) r = (unsigned long long)r * a % mod;
        a = (unsigned long long)a * a % mod;
        n >>= 1;
    }
    return r;
}

long long mod_sqrt(long long a, long long p) {
    a %= p;
    if (a < 0) a += p;
    if (a == 0 || p == 2) return a;
    if (mod_pow(a, (p - 1) >> 1, p) != 1) return -1;
    if (p % 4 == 3) return mod_pow(a, (p + 1) >> 2, p);

    long long q = p - 1;
    int s = 0;
    while ((q & 1) == 0) {
        ++s;
        q >>= 1;
    }
    long long z = 2;
    while (mod_pow(z, (p - 1) >> 1, p) == 1) ++z;
    long long c = mod_pow(z, q, p);
    long long t = mod_pow(a, q, p);
    long long r = mod_pow(a, (q + 1) >> 1, p);
    int m = s;
    while (t != 1) {
        int i = 1;
        long long tt = (unsigned long long)t * t % p;
        while (i < m && tt != 1) {
            tt = (unsigned long long)tt * tt % p;
            ++i;
        }
        long long b = mod_pow(c, 1LL << (m - i - 1), p);
        r = (unsigned long long)r * b % p;
        c = (unsigned long long)b * b % p;
        t = (unsigned long long)t * c % p;
        m = i;
    }
    return r;
}

/**
 * @brief 平方根 (mod p)
 */
