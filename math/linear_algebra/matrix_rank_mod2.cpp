#ifndef FIRIEXP_LIBRARY_MATH_MATRIX_RANK_MOD2_CPP
#define FIRIEXP_LIBRARY_MATH_MATRIX_RANK_MOD2_CPP

#include "../../datastructure/bitset/dynamic_bitset.cpp"

int matrix_rank_mod2(vector<DynamicBitset> a) {
    int n = (int)a.size();
    int m = a.empty() ? 0 : a[0].size();
    for ([[maybe_unused]] const auto &row : a) assert(row.size() == m);
    int rank = 0;
    for (int col = 0; col < m && rank < n; ++col) {
        int pivot = rank;
        while (pivot < n && !a[pivot].test(col)) ++pivot;
        if (pivot == n) continue;
        swap(a[pivot], a[rank]);
        for (int i = rank + 1; i < n; ++i) {
            if (a[i].test(col)) a[i].xor_from_word(a[rank], col / 64);
        }
        ++rank;
    }
    return rank;
}

#endif

/**
 * @brief mod 2の行列の階数
 */
