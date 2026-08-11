#include "miller_rabin.cpp"

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

constexpr int pollard_pm1_bound = 3000;
const auto primes = get_prime(pollard_pm1_bound);

constexpr ull pollard_batch_size = 208;
constexpr ull pollard_pm1_trigger = 2048;
constexpr ull pollard_pm1_mod_threshold = 500000000000000000ULL;
constexpr ull pollard_lazy_mod_limit = 1ULL << 61;

// REDC の結果を正規化しない。mod < 2^61 なら rho 内の値は 4 * mod 未満に収まる。
struct mod64_lazy {
    ull n;
    static ull mod, inv, r2;
    mod64_lazy() : n(0) {}
    mod64_lazy(ull x) : n(init(x)) {}
    static void set_mod(ull m) {
        mod = inv = m;
        for (int i = 0; i < 5; ++i) inv *= 2 - inv * m;
        inv = -inv;
        r2 = -u128(m) % m;
    }
    static ull reduce(u128 x) {
        ull q = (ull)x * inv;
        return (x + u128(q) * mod) >> 64;
    }
    static ull init(ull x) {
        ull y = reduce(u128(x) * r2);
        return y >= mod ? y - mod : y;
    }
    mod64_lazy& operator*=(mod64_lazy x) {
        n = reduce(u128(n) * x.n);
        return *this;
    }
    mod64_lazy& operator+=(mod64_lazy x) {
        n += x.n;
        return *this;
    }
};

ull mod64_lazy::mod, mod64_lazy::inv, mod64_lazy::r2;

vector<ull> get_pollard_pm1_exponents() {
    vector<ull> res;
    ull product = 1;
    for (auto &&p : primes) {
        if (p.val > pollard_pm1_bound) break;
        ull power = p.val;
        while (power <= pollard_pm1_bound / p.val) power *= p.val;
        if (product > ull(-1) / power) {
            res.emplace_back(product);
            product = 1;
        }
        product *= power;
    }
    res.emplace_back(product);
    return res;
}

const auto pollard_pm1_exponents = get_pollard_pm1_exponents();

mt19937_64 rng(0x8a5cd789635d2dffULL);

mod64_lazy pow_mod64_lazy(mod64_lazy x, ull exponent) {
    mod64_lazy res = x;
    for (int bit = 62 - __builtin_clzll(exponent); bit >= 0; --bit) {
        res *= res;
        if ((exponent >> bit) & 1) res *= x;
    }
    return res;
}

ull pollard_pm1(ull n) {
    mod64_lazy::set_mod(n);
    mod64_lazy x(2), one(1);
    for (ull exponent : pollard_pm1_exponents) {
        x = pow_mod64_lazy(x, exponent);
    }
    ull diff = x.n > one.n ? x.n - one.n : one.n - x.n;
    ull g = gcd(diff, n);
    return g != 1 && g != n ? g : 0;
}

template<class Mint>
ull pollard_rho_impl(ull nn, bool use_pm1) {
    uniform_int_distribution<ull> ra(1, nn - 1);
    Mint::set_mod(nn);
    bool pm1_done = !use_pm1;
    while(true){
        ull c_ = ra(rng), g = 1, r = 1;
        while(c_ == nn - 2) c_ = ra(rng);
        Mint y(ra(rng)), xx(0), c(c_), ys(0), q(1);
        while(g == 1){
            xx.n = y.n;
            for (ull i = 0; i < r; ++i) {
                y *= y; y += c;
            }
            ull k = 0; g = 1;
            while(k < r && g == 1){
                ull lim = min(pollard_batch_size, r - k);
                for (ull i = 0; i < lim; ++i) {
                    ys.n = y.n;
                    y *= y; y += c;
                    Mint diff;
                    diff.n = xx.n > y.n ? xx.n - y.n : y.n - xx.n;
                    q *= diff;
                }
                g = gcd<ull>(q.n, nn);
                k += pollard_batch_size;
            }
            r *= 2;
            if (!pm1_done && r == pollard_pm1_trigger) {
                ull factor = pollard_pm1(nn);
                if (factor != 0) return factor;
                pm1_done = true;
            }
        }
        if(g == nn) g = 1;
        while (g == 1){
            ys *= ys; ys += c;
            ull diff = xx.n > ys.n ? xx.n - ys.n : ys.n - xx.n;
            g = gcd<ull>(diff, nn);
        }
        if (g != nn) return g;
    }
}

template<class T>
T pollard_rho2(T n) {
    ull nn = n;
    if ((nn & 1) == 0) return 2;
    if (nn < pollard_lazy_mod_limit) {
        return (T)pollard_rho_impl<mod64_lazy>(nn, nn >= pollard_pm1_mod_threshold);
    }
    return (T)pollard_rho_impl<mod64>(nn, false);
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
    ull root = __builtin_sqrtl((long double)n);
    while ((u128)(root + 1) * (root + 1) <= (ull)n) ++root;
    while ((u128)root * root > (ull)n) --root;
    if ((u128)root * root == (ull)n) {
        prime_factor_impl((T)root, res, false);
        prime_factor_impl((T)root, res, false);
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
