#ifndef FIRIEXP_LIBRARY_MATH_MODULAR_GARNER_CPP
#define FIRIEXP_LIBRARY_MATH_MODULAR_GARNER_CPP

#include "modinv.cpp"

ll Garner(vector<pair<ll, ll>> equations, ll mod) {
    size_t n = equations.size();
    equations.emplace_back(0, mod);
    vector<ll> coeff(n + 1, 1), residue(n + 1, 0);
    for (size_t i = 0; i < n; ++i) {
        auto [r, m] = equations[i];
        ll inverse = mod_inv(coeff[i], m);
        ll digit = (__int128(r) - residue[i]) * inverse % m;
        if (digit < 0) digit += m;
        for (size_t j = i + 1; j <= n; ++j) {
            ll next_mod = equations[j].second;
            residue[j] = (__uint128_t(digit) * coeff[j] + residue[j]) % next_mod;
            coeff[j] = __uint128_t(coeff[j]) * m % next_mod;
        }
    }
    return residue.back();
}

#endif

/**
 * @brief Garnerのアルゴリズム
 */
