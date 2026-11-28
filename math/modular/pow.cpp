#ifndef FIRIEXP_LIBRARY_MATH_MODULAR_POW_CPP
#define FIRIEXP_LIBRARY_MATH_MODULAR_POW_CPP

template <class T>
T pow_ (T x, T n, T M){
    unsigned __int128 u = 1 % M, xx = x;
    if constexpr (std::is_signed_v<T>) {
        if (x < 0) {
            T r = x % M;
            xx = r < 0 ? r + M : r;
        }
    }
    while (n > 0){
        if (n&1) u = u * xx % M;
        xx = xx * xx % M;
        n >>= 1;
    }
    return static_cast<T>(u);
};

/**
 * @brief 繰り返し二乗法
 */

#endif
