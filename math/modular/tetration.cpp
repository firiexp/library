#include "../prime/eulerphi.cpp"
#include "pow.cpp"

ll totient(ll n) {
    return eulerphi(n);
}

namespace tetration_detail {
bool at_least(ll a, ll n, ull limit) {
    if (a <= 1) return limit == 1 && (a == 1 || n % 2 == 0);
    while (n > 0 && limit > 1) {
        ull exponent = 0;
        for (unsigned __int128 power = 1; power < limit; power *= a) {
            ++exponent;
        }
        limit = exponent;
        --n;
    }
    return limit <= 1;
}
}

ll tetration(ll a, ll n, ll M) {
    if (M == 1) return 0;
    if (a == 0) return n % 2 == 0;
    if (a == 1 || n == 0) return 1;
    if (n == 1) return a % M;

    ull exponent = a;
    if (n > 2) {
        ll phi = totient(M);
        exponent = tetration(a, n - 1, phi);
        if (tetration_detail::at_least(a, n - 1, phi)) exponent += phi;
    }
    return pow_<ull>(a % M, exponent, M);
}

ull tetration(ll a, ll n, ll M, bool &large) {
    large = tetration_detail::at_least(a, n, M);
    return static_cast<ull>(tetration(a, n, M)) + (large ? M : 0);
}

/**
 * @brief Tetration Mod
 */
