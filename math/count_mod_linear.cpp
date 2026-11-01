#include "floor_sum.cpp"

ll count_mod_linear(ll n, ll m, ll a, ll b, ll l, ll r) {
    assert(0 <= n && n < (1LL << 32));
    assert(1 <= m && m < (1LL << 32));
    assert(0 <= l && l <= r && r <= m);
    if (n == 0 || l == r) return 0;
    if (l == 0 && r == m) return n;
    a %= m;
    b %= m;
    if (a < 0) a += m;
    if (b < 0) b += m;
    return floor_sum(n, m, a, b + m - l) - floor_sum(n, m, a, b + m - r);
}

/**
 * @brief 一次式の剰余の区間個数
 */
