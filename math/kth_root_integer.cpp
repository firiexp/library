using ull = unsigned long long;

bool kth_root_integer_leq(ull x, int k, ull a) {
    __uint128_t p = 1;
    for (int i = 0; i < k; ++i) {
        p *= x;
        if (p > a) return false;
    }
    return true;
}

ull kth_root_integer(ull a, int k) {
    if (k == 1 || a <= 1) return a;
    ull ng = min<ull>(a, (1ULL << 32)) + 1, ok = 0;
    while (ng - ok > 1) {
        ull mid = ok + (ng - ok) / 2;
        if (kth_root_integer_leq(mid, k, a)) ok = mid;
        else ng = mid;
    }
    return ok;
}

/**
 * @brief 整数k乗根(K-th Root Integer)
 * @docs _md/kth_root_integer.md
 */
