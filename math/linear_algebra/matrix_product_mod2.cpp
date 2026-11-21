#ifndef FIRIEXP_LIBRARY_MATH_MATRIX_PRODUCT_MOD2_CPP
#define FIRIEXP_LIBRARY_MATH_MATRIX_PRODUCT_MOD2_CPP

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

#endif

/**
 * @brief mod 2の行列積
 */
