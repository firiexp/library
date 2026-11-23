#ifndef FIRIEXP_LIBRARY_MATH_ISQRT_CPP
#define FIRIEXP_LIBRARY_MATH_ISQRT_CPP

ull Isqrt(ull const &x){
    ull ret = (ull)sqrtl(x);
    while(ret > 0 && ret*ret > x) --ret;
    while(x - ret*ret > 2*ret) ++ret;
    return ret;
}

#endif

/**
 * @brief 整数平方根(Integer Square Root)
 */
