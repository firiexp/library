#include "./isqrt.cpp"

vector<ll> sqrt_fraction(ll n) {
    ll a0 = Isqrt(n);
    vector<ll> ret{a0};
    if (a0 * a0 == n) return ret;
    ll m = 0, d = 1, a = a0;
    do {
        m = (__int128)d * a - m;
        d = ((__int128)n - (__int128)m * m) / d;
        a = (a0 + m) / d;
        ret.push_back(a);
    } while (a != 2 * a0);
    return ret;
}

pair<ll, ll> pell_equation(ll d) {
    auto li = sqrt_fraction(d);
    if (li.size() <= 1) return {0, 0};
    li.pop_back();
    __int128 p = li.back(), q = 1;
    for (int i = (int)li.size() - 2; i >= 0; --i) {
        swap(p, q);
        p += q * li[i];
        assert(p <= LLONG_MAX && q <= LLONG_MAX);
    }
    if (p * p - d * q * q == -1) {
        __int128 x = p * p + d * q * q;
        q = 2 * p * q;
        p = x;
    }
    assert(p <= LLONG_MAX && q <= LLONG_MAX);
    return {(ll)p, (ll)q};
}
