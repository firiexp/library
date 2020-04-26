---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :warning: math/primefactor_ll.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#7e676e9e663beb40fd133f5ee24487c2">math</a>
* <a href="{{ site.github.repository_url }}/blob/master/math/primefactor_ll.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-26 17:42:59+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <random>
template< class T>
T pow_ (T x, uint64_t n, uint64_t M){
    T u = 1;
    if(n > 0){
        u = pow_(x, n/2, M);
        if (n % 2 == 0) u = (u*u) % M;
        else u = (((u * u)% M) * x) % M;
    }
    return u;
};

bool suspect(__uint128_t a, uint64_t s, uint64_t d, uint64_t n){
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
    uint64_t n = m;
    if (n <= 1 || (n > 2 && n % 2 == 0)) return false;
    uint64_t d = n - 1, s = 0;
    while (!(d&1)) {++s; d >>= 1;}
    vector<uint64_t> v = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    if(n <= 4759123141LL) v = {2, 7, 61};
    for (auto &&p : v) {
        if(p >= n) break;
        if(!suspect(p, s, d, n)) return false;
    }
    return true;
}

vector<int> get_prime(int n){
    if(n <= 1) return vector<int>();
    vector<bool> is_prime(n+1, true);
    vector<int> prime;
    is_prime[0] = is_prime[1] = 0;
    for (int i = 2; i <= n; ++i) {
        if(is_prime[i]) prime.emplace_back(i);
        for (auto &&j : prime){
            if(i*j > n) break;
            is_prime[i*j] = false;
            if(i % j == 0) break;
        }
    }
    return prime;
}

const auto primes = get_prime(100000);
random_device rng;
template<class T>
T pollard_rho2(T n) {
    uniform_int_distribution<T> ra(1, n-1);
    while(true){
        T c = ra(rng), g = 1, r = 1, y = ra(rng),m = 1900,
                ys = 0, q = 1, xx = 0;
        while(c == n-2) c = ra(rng);
        while(g == 1){
            xx = y;
            for (int i = 1; i <= r; ++i) {
                y = static_cast<T>(((__uint128_t)y * y) % n);
                y = static_cast<T>((__uint128_t)y + c) % n;
            }
            T k = 0; g = 1;
            while(k < r && g == 1){
                for (int i = 1; i <= (m > (r-k) ? (r-k) : m); ++i) {
                    ys = y;
                    y = static_cast<T>(((__uint128_t)y * y) % n);
                    y = static_cast<T>((__uint128_t)y + c) % n;
                    q = static_cast<T>(((__uint128_t)q * (xx > y ? xx - y : y - xx)) % n);
                }
                g = __gcd(q, n);
                k += m;
            }
            r *= 2;
        }
        if(g == n) g = 1;
        while (g == 1){
            ys = static_cast<T>(((__uint128_t)ys * ys) % n);
            ys = static_cast<T>((__uint128_t)ys + c) % n;
            g = __gcd(xx > ys ? xx - ys : ys - xx, n);
        }
        if (g != n && miller_rabin(g)) return g;
    }
}

template<class T>
vector<T> prime_factor(T n, int d = 0){
    vector<T> a, res;
    if(!d) for (auto &&i : primes) {
            while (n % i == 0){
                res.emplace_back(i);
                n /= i;
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
    return res;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "math/primefactor_ll.cpp"
#include <random>
template< class T>
T pow_ (T x, uint64_t n, uint64_t M){
    T u = 1;
    if(n > 0){
        u = pow_(x, n/2, M);
        if (n % 2 == 0) u = (u*u) % M;
        else u = (((u * u)% M) * x) % M;
    }
    return u;
};

bool suspect(__uint128_t a, uint64_t s, uint64_t d, uint64_t n){
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
    uint64_t n = m;
    if (n <= 1 || (n > 2 && n % 2 == 0)) return false;
    uint64_t d = n - 1, s = 0;
    while (!(d&1)) {++s; d >>= 1;}
    vector<uint64_t> v = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    if(n <= 4759123141LL) v = {2, 7, 61};
    for (auto &&p : v) {
        if(p >= n) break;
        if(!suspect(p, s, d, n)) return false;
    }
    return true;
}

vector<int> get_prime(int n){
    if(n <= 1) return vector<int>();
    vector<bool> is_prime(n+1, true);
    vector<int> prime;
    is_prime[0] = is_prime[1] = 0;
    for (int i = 2; i <= n; ++i) {
        if(is_prime[i]) prime.emplace_back(i);
        for (auto &&j : prime){
            if(i*j > n) break;
            is_prime[i*j] = false;
            if(i % j == 0) break;
        }
    }
    return prime;
}

const auto primes = get_prime(100000);
random_device rng;
template<class T>
T pollard_rho2(T n) {
    uniform_int_distribution<T> ra(1, n-1);
    while(true){
        T c = ra(rng), g = 1, r = 1, y = ra(rng),m = 1900,
                ys = 0, q = 1, xx = 0;
        while(c == n-2) c = ra(rng);
        while(g == 1){
            xx = y;
            for (int i = 1; i <= r; ++i) {
                y = static_cast<T>(((__uint128_t)y * y) % n);
                y = static_cast<T>((__uint128_t)y + c) % n;
            }
            T k = 0; g = 1;
            while(k < r && g == 1){
                for (int i = 1; i <= (m > (r-k) ? (r-k) : m); ++i) {
                    ys = y;
                    y = static_cast<T>(((__uint128_t)y * y) % n);
                    y = static_cast<T>((__uint128_t)y + c) % n;
                    q = static_cast<T>(((__uint128_t)q * (xx > y ? xx - y : y - xx)) % n);
                }
                g = __gcd(q, n);
                k += m;
            }
            r *= 2;
        }
        if(g == n) g = 1;
        while (g == 1){
            ys = static_cast<T>(((__uint128_t)ys * ys) % n);
            ys = static_cast<T>((__uint128_t)ys + c) % n;
            g = __gcd(xx > ys ? xx - ys : ys - xx, n);
        }
        if (g != n && miller_rabin(g)) return g;
    }
}

template<class T>
vector<T> prime_factor(T n, int d = 0){
    vector<T> a, res;
    if(!d) for (auto &&i : primes) {
            while (n % i == 0){
                res.emplace_back(i);
                n /= i;
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
    return res;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

