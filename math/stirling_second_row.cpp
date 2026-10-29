#ifndef FIRIEXP_LIBRARY_MATH_STIRLING_SECOND_ROW_CPP
#define FIRIEXP_LIBRARY_MATH_STIRLING_SECOND_ROW_CPP

#include "ntt.cpp"
#include "factorial.cpp"
#include "powk_all.cpp"

vector<mint> stirling_second_row(long long n, int k) {
    assert(n >= 0 && 0 <= k && k < (1 << 22));
    if (n == 0) {
        vector<mint> result(k + 1);
        result[0] = 1;
        return result;
    }
    if (k == 0) return {mint(0)};
    int degree = (int)min(n, (long long)k);
    Factorial<> factorial(degree);
    poly a(powk_all(degree, n)), b(degree + 1);
    for (int j = 0; j <= degree; ++j) {
        mint inverse = factorial.inv_fact(j);
        a[j] *= inverse;
        b[j] = j % 2 ? -inverse : inverse;
    }
    a *= b;
    a.v.resize(degree + 1);
    a.v.resize(k + 1);
    return move(a.v);
}

#endif

/**
 * @brief 第二種Stirling数の列
 */
