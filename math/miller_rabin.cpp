using u128 = __uint128_t;

struct mod64 {
    unsigned long long n;
    static unsigned long long mod, inv, r2;
    mod64() : n(0) {}
    mod64(unsigned long long x) : n(init(x)) {}
    static unsigned long long init(unsigned long long w) {
        return reduce(u128(w) * r2);
    }
    static void set_mod(unsigned long long m) {
        mod = inv = m;
        for (int i = 0; i < 5; ++i) inv *= 2 - inv * m;
        r2 = -u128(m) % m;
    }
    static unsigned long long reduce(u128 x) {
        unsigned long long y =
            static_cast<unsigned long long>(x >> 64)
            - static_cast<unsigned long long>((u128(static_cast<unsigned long long>(x) * inv) * mod) >> 64);
        return (long long)y < 0 ? y + mod : y;
    }
    mod64& operator*=(mod64 x) {
        n = reduce(u128(n) * x.n);
        return *this;
    }
    mod64 operator*(mod64 x) const {
        return mod64(*this) *= x;
    }
    mod64& operator+=(mod64 x) {
        n += x.n - mod;
        if((long long)n < 0) n += mod;
        return *this;
    }
    mod64 operator+(mod64 x) const {
        return mod64(*this) += x;
    }
    unsigned long long val() const {
        return reduce(n);
    }
};

unsigned long long mod64::mod, mod64::inv, mod64::r2;

bool suspect(unsigned long long a, unsigned long long s, unsigned long long d, unsigned long long n){
    if(mod64::mod != n) mod64::set_mod(n);
    mod64 x(1), xx(a), one(1), minusone(n - 1);
    while(d > 0){
        if(d & 1) x *= xx;
        xx *= xx;
        d >>= 1;
    }
    if (x.n == one.n) return true;
    for (unsigned long long r = 0; r < s; ++r) {
        if(x.n == minusone.n) return true;
        x *= x;
    }
    return false;
}

template<class T>
bool miller_rabin(T m){
    unsigned long long n = m;
    if (n <= 1 || (n > 2 && n % 2 == 0)) return false;
    if (n == 2 || n == 3 || n == 5 || n == 7) return true;
    if (n % 3 == 0 || n % 5 == 0 || n % 7 == 0) return false;
    unsigned long long d = n - 1, s = 0;
    while (!(d & 1)) { ++s; d >>= 1; }
    static constexpr unsigned long long small[] = {2, 7, 61};
    static constexpr unsigned long long large[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    if(n < 4759123141ULL) {
        for (auto p : small) {
            if(p >= n) break;
            if(!suspect(p, s, d, n)) return false;
        }
    } else {
        for (auto p : large) {
            if(p >= n) break;
            if(!suspect(p, s, d, n)) return false;
        }
    }
    return true;
}

/**
 * @brief Miller-Rabin素数判定
 */
