ll min_of_mod_of_linear(ll n, ll m, ll a, ll b) {
    ll ans = b;
    while (true) {
        if (a > m / 2) {
            b = ((__int128)a * (n - 1) + b) % m;
            a = m - a;
        }
        ans = min(ans, b);
        if (a == 0) return ans;
        ll k = ((__int128)a * (n - 1) + b) / m;
        if (k == 0) return ans;
        ll next_a = (a - m % a) % a;
        ll next_b = (b - m) % a;
        if (next_b < 0) next_b += a;
        n = k;
        m = a;
        a = next_a;
        b = next_b;
    }
}

/**
 * @brief 一次式の剰余の最小値
 */
