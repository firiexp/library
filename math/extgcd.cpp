#ifndef FIRIEXP_LIBRARY_MATH_EXTGCD_CPP
#define FIRIEXP_LIBRARY_MATH_EXTGCD_CPP

template<typename T>
T extgcd(T a, T b, T &x ,T &y){
    using std::swap;
    for (T u = y = 1, v = x = 0; a; ) {
        ll q = b/a;
        swap(x -= q*u, u);
        swap(y -= q*v, v);
        swap(b -= q*a, a);
    }
    return b;
}

#endif

/**
 * @brief 拡張ユークリッド互除法(Extended GCD)
 */
