#include <algorithm>
#include <array>
#include <numeric>
#include <random>

using ull = unsigned long long;
using u128 = __uint128_t;

template<class T>
T pow_(T x, ull n, ull M){
    T r = 1;
    while(n){
        if(n & 1) r = (u128)r * x % M;
        x = (u128)x * x % M;
        n >>= 1;
    }
    return r;
}

bool suspect(__uint128_t a, ull s, ull d, ull n){
    __uint128_t x = pow_(a, d, n);
    if (x == 1) return true;
    for (ull r = 0; r < s; ++r) {
        if(x == n-1) return true;
        x = x * x % n;
    }
    return false;
}

template<class T>
bool miller_rabin(T m){
    ull n = m;
    if (n <= 1 || (n > 2 && n % 2 == 0)) return false;
    if (n == 2 || n == 3 || n == 5 || n == 7) return true;
    if (n % 3 == 0 || n % 5 == 0 || n % 7 == 0) return false;
    ull d = n - 1, s = 0;
    while (!(d&1)) {++s; d >>= 1;}
    static constexpr array<ull, 3> small = {2, 7, 61};
    static constexpr array<ull, 7> large = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    if (n <= 4759123141ULL) {
        for (ull p : small) {
            if(p >= n) break;
            if(!suspect(p, s, d, n)) return false;
        }
    } else {
        for (ull p : large) {
            if(p >= n) break;
            if(!suspect(p, s, d, n)) return false;
        }
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
            ull v = (ull)i * j.val;
            if(v > (ull)n) break;
            is_prime[v] = false;
            if(j.divide(i)) break;
        }
    }
    return prime;
}
const auto primes = get_prime(50000);

mt19937_64 rng(0x8a5cd789635d2dffULL);

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
    ull nn = n;
    if ((nn & 1) == 0) return 2;
    uniform_int_distribution<ull> ra(1, nn - 1);
    mod64::set_mod(nn);
    while(true){
        ull c_ = ra(rng), g = 1, r = 1, m = 500;
        while(c_ == nn - 2) c_ = ra(rng);
        mod64 y(ra(rng)), xx(0), c(c_), ys(0), q(1);
        while(g == 1){
            xx.n = y.n;
            for (ull i = 0; i < r; ++i) {
                y *= y; y += c;
            }
            ull k = 0; g = 1;
            while(k < r && g == 1){
                ull lim = min(m, r - k);
                for (ull i = 0; i < lim; ++i) {
                    ys.n = y.n;
                    y *= y; y += c;
                    ull xxx = xx.val(), yyy = y.val();
                    q *= mod64(xxx > yyy ? xxx - yyy : yyy - xxx);
                }
                g = gcd<ull>(q.val(), nn);
                k += m;
            }
            r *= 2;
        }
        if(g == nn) g = 1;
        while (g == 1){
            ys *= ys; ys += c;
            ull xxx = xx.val(), yyy = ys.val();
            g = gcd<ull>(xxx > yyy ? xxx - yyy : yyy - xxx, nn);
        }
        if (g != nn && miller_rabin(g)) return (T)g;
    }
}

template<class T>
void prime_factor_impl(T n, vector<T> &res, bool trial){
    if(trial) {
        for (auto &&i : primes) {
            while (i.divide(n)){
                res.emplace_back(i.val);
                n /= i.val;
            }
        }
    }
    if(n == 1) return;
    if(miller_rabin(n)) {
        res.emplace_back(n);
        return;
    }
    T x = pollard_rho2(n);
    prime_factor_impl(x, res, false);
    prime_factor_impl(n / x, res, false);
}

template<class T>
vector<T> prime_factor(T n){
    vector<T> res;
    prime_factor_impl(n, res, true);
    sort(res.begin(),res.end());
    return res;
}

/**
 * @brief 素因数分解(Pollard Rho)
 */
