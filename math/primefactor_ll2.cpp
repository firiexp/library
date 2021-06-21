#include <random>

using ull = unsigned long long;
using u128 = __uint128_t;

template< class T>
T pow_ (T x, ull n, ull M){
    T u = 1;
    if(n > 0){
        u = pow_(x, n/2, M);
        if (n % 2 == 0) u = (u*u) % M;
        else u = (((u * u)% M) * x) % M;
    }
    return u;
};

bool suspect(__uint128_t a, ull s, ull d, ull n){
    __uint128_t x = pow_(a, d, n);
    if (x == 1) return true;
    for (int r = 0; r < s; ++r) {
        if(x == n-1) return true;
        x = x * x % n;
    }
    return false;
}

template<class T>
bool miller_rabin(T m){
    ull n = m;
    if (n <= 1 || (n > 2 && n % 2 == 0)) return false;
    ull d = n - 1, s = 0;
    while (!(d&1)) {++s; d >>= 1;}
    vector<ull> v = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    if(n <= 4759123141LL) v = {2, 7, 61};
    for (auto &&p : v) {
        if(p >= n) break;
        if(!suspect(p, s, d, n)) return false;
    }
    return true;
}


template<typename T>
struct ExactDiv {
    T t, i, val;
    ExactDiv() {}
    ExactDiv(T n) : t(T(-1) / n), i(mul_inv(n)) , val(n) {};
    T mul_inv(T n) {
        T x = n;
        for (int i = 0; i < 5; ++i) x *= 2 - n * x;
        return x;
    }
    bool divide(T n) const {
        if(val == 2) return !(n & 1);
        return n * this->i <= this->t;
    }
};

vector<ExactDiv<ull>> get_prime(int n){
    if(n <= 1) return vector<ExactDiv<ull>>();
    vector<bool> is_prime(n+1, true);
    vector<ExactDiv<ull>> prime;
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= n; ++i) {
        if(is_prime[i]) prime.emplace_back(i);
        for (auto &&j : prime){
            if(i*j.val > n) break;
            is_prime[i*j.val] = false;
            if(j.divide(i)) break;
        }
    }
    return prime;
}
const auto primes = get_prime(50000);

random_device rng;

struct mod64 {
    ull n;
    static ull mod, inv, r2;
    mod64() : n(0) {}
    mod64(ull x) : n(init(x)) {}
    static ull init(ull w) { return reduce(u128(w) * r2); }
    static void set_mod(ull m) {
        mod = inv = m;
        for (int i = 0; i < 5; ++i) inv *= 2 - inv * m;
        r2 = -u128(m) % m;
    }
    static ull reduce(u128 x) {
        ull y = ull(x >> 64) - ull((u128(ull(x) * inv) * mod) >> 64);
        return ll(y) < 0 ? y + mod : y;
    };
    mod64& operator+=(mod64 x) { n += x.n - mod; if(ll(n) < 0) n += mod; return *this; }
    mod64 operator+(mod64 x) const { return mod64(*this) += x; }
    mod64& operator*=(mod64 x) { n = reduce(u128(n) * x.n);  return *this; }
    mod64 operator*(mod64 x) const { return mod64(*this) *= x; }
    ull val() const { return reduce(n); }
};

ull mod64::mod, mod64::inv, mod64::r2;

template<class T>
T pollard_rho2(T n) {
    uniform_int_distribution<T> ra(1, n-1);
    mod64::set_mod(n);
    while(true){
        ull c_ = ra(rng), g = 1, r = 1, m = 500;
        while(c_ == n-2) c_ = ra(rng);
        mod64 y(ra(rng)), xx(0), c(c_), ys(0), q(1);
        while(g == 1){
            xx.n = y.n;
            for (int i = 1; i <= r; ++i) {
                y *= y; y += c;
            }
            T k = 0; g = 1;
            while(k < r && g == 1){
                for (int i = 1; i <= (m > (r-k) ? (r-k) : m); ++i) {
                    ys.n = y.n;
                    y *= y; y += c;
                    ull xxx = xx.val(), yyy = y.val();
                    q *= mod64(xxx > yyy ? xxx - yyy : yyy - xxx);
                }
                g = __gcd<ll>(q.val(), n);
                k += m;
            }
            r *= 2;
        }
        if(g == n) g = 1;
        while (g == 1){
            ys *= ys; ys += c;
            ull xxx = xx.val(), yyy = ys.val();
            g = __gcd<ll>(xxx > yyy ? xxx - yyy : yyy - xxx, n);
        }
        if (g != n && miller_rabin(g)) return g;
    }
}

template<class T>
vector<T> prime_factor(T n, int d = 0){
    vector<T> a, res;
    if(!d) for (auto &&i : primes) {
            while (i.divide(n)){
                res.emplace_back(i.val);
                n /= i.val;
            }
        }
    while(n != 1){
        if(miller_rabin(n)){
            a.emplace_back(n);
            break;
        }
        T x = pollard_rho2(n);
        n /= x;
        a.emplace_back(x);
    }
    for (auto &&i : a) {
        if (miller_rabin(i)) {
            res.emplace_back(i);
        } else {
            vector<T> b = prime_factor(i, d + 1);
            for (auto &&j : b) res.emplace_back(j);
        }
    }
    sort(res.begin(),res.end());
    return res;
}