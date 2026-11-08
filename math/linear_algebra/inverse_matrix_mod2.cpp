#ifndef FIRIEXP_LIBRARY_MATH_INVERSE_MATRIX_MOD2_CPP
#define FIRIEXP_LIBRARY_MATH_INVERSE_MATRIX_MOD2_CPP

#include "../../datastructure/bitset/dynamic_bitset.cpp"

vector<DynamicBitset> inverse_matrix_mod2(vector<DynamicBitset> a) {
    int n = (int)a.size();
    for (const auto &row : a) assert(row.size() == n);
    vector<DynamicBitset> inverse(n, DynamicBitset(n));
    for (int i = 0; i < n; ++i) inverse[i].set(i);
    for (int col = 0; col < n; ++col) {
        int pivot = col;
        while (pivot < n && !a[pivot].test(col)) ++pivot;
        if (pivot == n) return {};
        swap(a[pivot], a[col]);
        swap(inverse[pivot], inverse[col]);
        for (int row = 0; row < n; ++row) {
            if (row == col || !a[row].test(col)) continue;
            a[row] ^= a[col];
            inverse[row] ^= inverse[col];
        }
    }
    return inverse;
}

#endif

/**
 * @brief mod 2の逆行列
 */
