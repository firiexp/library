template <class T>
T mod_inv(T x, T M) {
    assert(M >= 1);
    if (M == 1) return 0;
    x %= M;
    if (x < 0) x += M;

    T m = M, coeff = 0, next_coeff = 1;
    bool negative = true;
    while (x != 0) {
        T q = m / x;
        m -= q * x;
        swap(m, x);
        coeff += q * next_coeff;
        swap(coeff, next_coeff);
        negative = !negative;
    }
    assert(m == 1);
    return negative ? M - coeff : coeff;
}

/**
 * @brief MOD逆元(拡張ユークリッド互除法)
 */
