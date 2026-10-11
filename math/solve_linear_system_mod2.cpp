#ifndef FIRIEXP_LIBRARY_MATH_SOLVE_LINEAR_SYSTEM_MOD2_CPP
#define FIRIEXP_LIBRARY_MATH_SOLVE_LINEAR_SYSTEM_MOD2_CPP

#include "../datastructure/dynamic_bitset.cpp"

struct LinearSystemSolutionMod2 {
    int rank;
    DynamicBitset particular;
    vector<DynamicBitset> basis;
};

optional<LinearSystemSolutionMod2> solve_linear_system_mod2(
    vector<DynamicBitset> a, DynamicBitset b, int variables = -1) {
    int n = (int)a.size();
    assert(variables >= -1 && b.size() == n);
    int m = variables < 0 ? (n ? a[0].size() : 0) : variables;
    for (const auto& row : a) assert(row.size() == m);
    vector<int> pivot, where(m, -1);
    int rank = 0;
    for (int col = 0; col < m && rank < n; ++col) {
        int row = rank;
        while (row < n && !a[row].test(col)) ++row;
        if (row == n) continue;
        swap(a[row], a[rank]);
        bool value = b.test(row);
        b.assign(row, b.test(rank));
        b.assign(rank, value);
        for (int i = 0; i < n; ++i) {
            if (i == rank || !a[i].test(col)) continue;
            a[i] ^= a[rank];
            if (value) b.flip(i);
        }
        where[col] = rank++;
        pivot.push_back(col);
    }
    for (int i = rank; i < n; ++i) if (b.test(i)) return nullopt;

    LinearSystemSolutionMod2 result{rank, DynamicBitset(m), {}};
    for (int i = 0; i < rank; ++i) result.particular.assign(pivot[i], b.test(i));
    result.basis.reserve(m - rank);
    for (int col = 0; col < m; ++col) {
        if (where[col] != -1) continue;
        DynamicBitset v(m);
        v.set(col);
        for (int i = 0; i < rank; ++i) v.assign(pivot[i], a[i].test(col));
        result.basis.push_back(std::move(v));
    }
    return result;
}

#endif

/**
 * @brief mod 2の連立一次方程式(基底・特殊解)
 */
