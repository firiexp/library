#ifndef FIRIEXP_LIBRARY_MATH_STIRLING_FIRST_ROW_CPP
#define FIRIEXP_LIBRARY_MATH_STIRLING_FIRST_ROW_CPP

#include "../../fps/taylor_shift.cpp"

vector<mint> stirling_first_row_unsigned(int n) {
    assert(0 <= n && n < (1 << 23));
    if (n == 0) return {1};
    int m = n / 2;
    poly row(stirling_first_row_unsigned(m));
    row *= taylor_shift(row, m);
    if (n % 2) {
        mint c = 2 * m;
        row.v.emplace_back();
        for (int k = n; k > 0; --k) row[k] = row[k - 1] + c * row[k];
        row[0] *= c;
    }
    return move(row.v);
}

vector<mint> stirling_first_row(int n) {
    auto row = stirling_first_row_unsigned(n);
    for (int k = n - 1; k >= 0; k -= 2) row[k] = -row[k];
    return row;
}

#endif

/**
 * @brief 第一種Stirling数の列
 */
