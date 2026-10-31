#ifndef FIRIEXP_LIBRARY_MATH_PARTITION_NUMBERS_CPP
#define FIRIEXP_LIBRARY_MATH_PARTITION_NUMBERS_CPP

#include "../../fps/ntt.cpp"

vector<mint> partition_numbers(int n) {
    assert(0 <= n && n < (1 << 23));
    poly denominator(n + 1);
    denominator[0] = 1;
    for (long long k = 1; k * (3 * k - 1) / 2 <= n; ++k) {
        mint sign = k % 2 ? -mint(1) : mint(1);
        denominator[k * (3 * k - 1) / 2] = sign;
        long long other = k * (3 * k + 1) / 2;
        if (other <= n) denominator[other] = sign;
    }
    return denominator.inv(n + 1).v;
}

#endif

/**
 * @brief 整数の分割数
 */
