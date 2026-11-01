#ifndef FIRIEXP_LIBRARY_MATH_QUOTIENT_RANGES_CPP
#define FIRIEXP_LIBRARY_MATH_QUOTIENT_RANGES_CPP

template<class F>
void for_each_quotient(long long n, F f, long long first = 1) {
    assert(n >= 0 && first >= 1);
    for (long long l = first; l <= n;) {
        long long q = n / l, r = n / q;
        f(l, r, q);
        if (r == n) break;
        l = r + 1;
    }
}

#endif

/**
 * @brief 商が一定の区間列挙
 */
