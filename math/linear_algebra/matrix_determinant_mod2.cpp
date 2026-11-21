#ifndef FIRIEXP_LIBRARY_MATH_MATRIX_DETERMINANT_MOD2_CPP
#define FIRIEXP_LIBRARY_MATH_MATRIX_DETERMINANT_MOD2_CPP

#include "matrix_rank_mod2.cpp"

int matrix_determinant_mod2(vector<DynamicBitset> a) {
    int n = (int)a.size();
    assert(a.empty() || a[0].size() == n);
    return matrix_rank_mod2(std::move(a)) == n;
}

#endif

/**
 * @brief mod 2の行列式
 */
