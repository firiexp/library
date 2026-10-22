#include "modinv.cpp"

struct BinomModPrimePower {
    ll p, mod;
    int q;
    ll block_prod;
    vector<ll> ppow;
    vector<int> prod, inv_prod;

    explicit BinomModPrimePower(ll prime, int exponent) : p(prime), mod(1), q(exponent), ppow(exponent + 1, 1) {
        for (int i = 0; i < q; ++i) {
            mod *= p;
            ppow[i + 1] = mod;
        }
        block_prod = (p == 2 && q >= 3 ? 1 : mod - 1);
        prod.assign(mod + 1, 1);
        for (int i = 1; i <= mod; ++i) {
            prod[i] = prod[i - 1];
            if (i % p != 0) prod[i] = (ull)prod[i] * i % mod;
        }
        if (q == 1) {
            inv_prod.resize(p);
            inv_prod[p - 1] = mod_inv<ll>(prod[p - 1], p);
            for (int i = p - 1; i > 0; --i) inv_prod[i - 1] = (ull)inv_prod[i] * i % p;
        }
    }

    pair<ll, ll> factorial(ll n) const {
        ll x = 1, e = 0;
        while (n) {
            if (block_prod != 1 && (n / mod) & 1) x = mod - x;
            x = (ull)x * prod[n % mod] % mod;
            n /= p;
            e += n;
        }
        return {x, e};
    }

    ll C(ll n, ll k) const {
        if (k < 0 || k > n) return 0;
        if (q == 1) {
            k = min(k, n - k);
            ll x = 1;
            while (k) {
                ll a = n % p, b = k % p;
                if (b > a) return 0;
                x = (ull)x * prod[a] % p * inv_prod[b] % p * inv_prod[a - b] % p;
                n /= p;
                k /= p;
            }
            return x;
        }
        auto [a, ea] = factorial(n);
        auto [b, eb] = factorial(k);
        auto [c, ec] = factorial(n - k);
        ll e = ea - eb - ec;
        if (e >= q) return 0;
        ll x = (ull)b * c % mod;
        return (ull)a * mod_inv(x, mod) % mod * ppow[e] % mod;
    }

    ll modulus() const {
        return mod;
    }
};

/**
 * @brief 二項係数(mod p^q)
 */
