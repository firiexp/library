#include "nth_term.cpp"
#include "../math/berlekamp_massey.cpp"

mint linear_recurrence(const vector<mint> &a, const vector<mint> &c, ll n) {
    if (n < (ll)a.size()) return a[(int)n];
    int k = (int)c.size();
    if (k == 0) return mint(0);
    poly q(k + 1);
    q[0] = 1;
    for (int i = 0; i < k; ++i) q[i + 1] = -c[i];
    vector<mint> aa(k, mint(0));
    for (int i = 0; i < min(k, (int)a.size()); ++i) aa[i] = a[i];
    poly p = (poly(aa) * q).cut(k);
    return nth_term(p, q, n);
}

mint linear_recurrence(const vector<mint> &a, ll n) {
    return linear_recurrence(a, berlekamp_massey(a), n);
}

/**
 * @brief linear recurrence
 * @docs _md/linear_recurrence.md
 */
