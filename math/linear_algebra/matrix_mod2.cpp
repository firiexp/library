#ifndef FIRIEXP_LIBRARY_MATH_MATRIX_MOD2_CPP
#define FIRIEXP_LIBRARY_MATH_MATRIX_MOD2_CPP

#include "../../datastructure/bitset/dynamic_bitset.cpp"

vector<DynamicBitset> matrix_product_mod2(const vector<DynamicBitset> &a,
                                          const vector<DynamicBitset> &b, int columns = -1) {
    assert(columns >= -1);
    int k = columns < 0 ? (b.empty() ? 0 : b[0].size()) : columns;
    for ([[maybe_unused]] const auto &row : b) assert(row.size() == k);
    vector<DynamicBitset> product;
    product.reserve(a.size());
    for (const auto &row : a) {
        assert((size_t)row.size() == b.size());
        auto &result = product.emplace_back(k);
        if (k == 0) continue;
        for (int j = row.find_first(); j != -1; j = row.find_next(j)) result ^= b[j];
    }
    return product;
}

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

int matrix_determinant_mod2(vector<DynamicBitset> a) {
    int n = (int)a.size();
    assert(a.empty() || a[0].size() == n);
    return matrix_rank_mod2(std::move(a)) == n;
}

#endif

/**
 * @brief mod 2の行列演算(積・階数・行列式)
 */
