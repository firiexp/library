#include "primefactor_ll2.cpp"
ll primitive_root(ll m) {
    if (m == 2) return 1;
    auto divs = prime_factor(m - 1);
    divs.erase(unique(divs.begin(), divs.end()), divs.end());
    auto mod_pow = [&](ll x, ll n) {
        ull a = x, r = 1, mod = m;
        while (n > 0) {
            if (n & 1) r = (u128)r * a % mod;
            a = (u128)a * a % mod;
            n >>= 1;
        }
        return (ll)r;
    };
    for (ll g = 2;; g++) {
        bool ok = true;
        for (auto &&d : divs) {
            if (mod_pow(g, (m - 1) / d) == 1) {
                ok = false;
                break;
            }
        }
        if (ok) return g;
    }
}
