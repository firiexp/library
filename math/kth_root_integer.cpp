ull kth_root_integer(ull a, ull k) {
    if (k == 1 || a <= 1) return a;
    unsigned bits = 64 - __builtin_clzll(a);
    if (k >= bits) return 1;
    ull low = 1ULL << ((bits - 1) / k);
    ull high = low * 2;
    int top_bit = 63 - __builtin_clzll(k);
    while (high - low > 1) {
        ull mid = (low + high) / 2;
        __uint128_t power = mid;
        for (int bit = top_bit - 1; bit >= 0; --bit) {
            power *= power;
            if ((k >> bit) & 1) power *= mid;
        }
        if (power <= a) low = mid;
        else high = mid;
    }
    return low;
}

/**
 * @brief 整数k乗根(K-th Root Integer)
 */
