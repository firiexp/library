ll floor_sum(ll n, ll m, ll a, ll b) {
    __int128 N = n, M = m, A = a, B = b, ans = 0;
    while (true) {
        __int128 qa = A / M - (A % M < 0);
        __int128 qb = B / M - (B % M < 0);
        ans += N * (N - 1) / 2 * qa + N * qb;
        A -= qa * M;
        B -= qb * M;
        __int128 y = A * N + B;
        if (y < M) return (ll)ans;
        N = y / M;
        B = y % M;
        __int128 next_m = A;
        A = M;
        M = next_m;
    }
}

/**
 * @brief Floor Sum
 */
