#ifndef FIRIEXP_LIBRARY_MATH_QUOTIENT_RANGES_CPP
#define FIRIEXP_LIBRARY_MATH_QUOTIENT_RANGES_CPP

template<class F>
void for_each_quotient(long long n, F f, long long first = 1) {
    assert(n >= 0 && first >= 1);
    if (first > n) return;
    long long l = first, q = n / l;
    while (q > l) {
        f(l, l, q);
        q = n / ++l;
    }
    while (q > 1) {
        long long r = n / q;
        f(l, r, q);
        l = r + 1;
        --q;
    }
    f(l, n, 1);
}

#endif

/**
 * @brief 商が一定の区間列挙
 */
