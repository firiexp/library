#include "primefactor_ll.cpp"
ll primitive_root(ll m) {
    if (m == 2) return 1;
    auto divs = prime_factor(m - 1);
    divs.erase(unique(divs.begin(), divs.end()), divs.end());
    mod64::set_mod(m);
    const mod64 one(1);
    auto mod_pow = [&](ll x, ll n) {
        mod64 a(x), r = one;
        while (n > 0) {
            if (n & 1) r *= a;
            a *= a;
            n >>= 1;
        }
        return r;
    };
    for (ll g = 2;; g++) {
        bool ok = true;
        for (auto &&d : divs) {
            if (mod_pow(g, (m - 1) / d).n == one.n) {
                ok = false;
                break;
            }
        }
        if (ok) return g;
    }
}

/**
 * @brief 原始根(Primitive Root)
 */
