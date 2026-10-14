#ifndef FIRIEXP_LIBRARY_MATH_BINOM_MOD_CPP
#define FIRIEXP_LIBRARY_MATH_BINOM_MOD_CPP

#include "binom_mod_prime_power.cpp"

class BinomMod {
    ll mod;
    vector<BinomModPrimePower> binoms;
    vector<ll> coefficients;

public:
    explicit BinomMod(ll modulus) : mod(modulus) {
        assert(1 <= mod && mod <= 1000000);
        ll remaining = mod;
        for (ll p = 2; p * p <= remaining; ++p) {
            if (remaining % p != 0) continue;
            int exponent = 0;
            do {
                remaining /= p;
                ++exponent;
            } while (remaining % p == 0);
            binoms.emplace_back(p, exponent);
        }
        if (remaining > 1) binoms.emplace_back(remaining, 1);
        for (const auto &binom : binoms) {
            ll power = binom.modulus(), cofactor = mod / power;
            coefficients.push_back(cofactor * mod_inv(cofactor % power, power) % mod);
        }
    }

    ll C(ll n, ll k) const {
        if (mod == 1 || k < 0 || k > n) return 0;
        ll result = 0;
        for (int i = 0; i < (int)binoms.size(); ++i)
            result = (result + binoms[i].C(n, k) * coefficients[i]) % mod;
        return result;
    }

    ll modulus() const { return mod; }
};

#endif

/**
 * @brief 二項係数（合成数mod）
 */
