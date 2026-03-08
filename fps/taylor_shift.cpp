#include "../math/ntt.cpp"

poly taylor_shift(const poly &f, mint c) {
    int n = f.size();
    if (n == 0) return poly();
    static vector<mint> fact = {mint(1)}, ifact = {mint(1)};
    auto ensure_fact = [&](int m) {
        if ((int)fact.size() > m) return;
        int old = fact.size();
        fact.resize(m + 1);
        for (int i = old; i <= m; ++i) fact[i] = fact[i - 1] * mint(i);
        ifact.resize(m + 1);
        ifact[m] = fact[m].inv();
        for (int i = m; i > old; --i) ifact[i - 1] = ifact[i] * mint(i);
        if (old == 1) ifact[0] = mint(1);
    };
    ensure_fact(n);
    poly a(n), b(n);
    mint pow_c = 1;
    for (int i = 0; i < n; ++i) {
        a[n - 1 - i] = f[i] * fact[i];
        b[i] = pow_c * ifact[i];
        pow_c *= c;
    }
    poly d = a * b;
    poly g(n);
    for (int i = 0; i < n; ++i) g[i] = d[n - 1 - i] * ifact[i];
    return g;
}

/**
 * @brief polynomial taylor shift
 * @docs _md/taylor_shift.md
 */
