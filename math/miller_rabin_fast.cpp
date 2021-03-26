using u128 = __uint128_t;

struct mod64 {
    u64 n;
    static u64 mod, inv, r2;
    mod64() : n(0) {}
    mod64(u64 x) : n(init(x)) {}
    static u64 init(u64 w) { return reduce(u128(w) * r2); }
    static void set_mod(u64 m) {
        mod = inv = m;
        for (int i = 0; i < 5; ++i) inv *= 2 - inv * m;
        r2 = -u128(m) % m;
    }
    static u64 reduce(u128 x) {
        u64 y = u64(x >> 64) - u64((u128(u64(x) * inv) * mod) >> 64);
        return ll(y) < 0 ? y + mod : y;
    };
    mod64& operator+=(mod64 x) { n += x.n - mod; if(ll(n) < 0) n += mod; return *this; }
    mod64 operator+(mod64 x) const { return mod64(*this) += x; }
    mod64& operator*=(mod64 x) { n = reduce(u128(n) * x.n);  return *this; }
    mod64 operator*(mod64 x) const { return mod64(*this) *= x; }
    u64 val() const { return reduce(n); }
};

u64 mod64::mod, mod64::inv, mod64::r2;

bool suspect(u64 a, u64 s, u64 d, u64 n){
    if(mod64::mod != n) mod64::set_mod(n);
    mod64 x(1), xx(a), one(x), minusone(n-1);
    while(d > 0){
        if(d&1) x = x * xx;
        xx = xx * xx;
        d >>= 1;
    }
    if (x.n == one.n) return true;
    for (int r = 0; r < s; ++r) {
        if(x.n == minusone.n) return true;
        x = x * x;
    }
    return false;
}

template<class T>
bool miller_rabin(T n){
    if (n <= 1 || (n > 2 && n % 2 == 0)) return false;
    u64 d = n - 1, s = 0;
    while (!(d&1)) {++s; d >>= 1;}
    vector<uint64_t> v = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    if(n < 4759123141LL) v = {2, 7, 61};
    for (auto &&p : v) {
        if(p >= n) break;
        if(!suspect(p, s, d, n)) return false;
    }
    return true;
}