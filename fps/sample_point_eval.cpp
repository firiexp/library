#ifndef FIRIEXP_LIBRARY_FPS_SAMPLE_POINT_EVAL_CPP
#define FIRIEXP_LIBRARY_FPS_SAMPLE_POINT_EVAL_CPP

#include "../math/combinatorics/factorial.cpp"

template <class Mint>
Mint sample_point_eval(const vector<Mint>& ys, Mint x) {
    int n = ys.size();
    if (n == 0) return Mint(0);
    assert(ys.size() <= Mint::get_mod());
    if (x.val < ys.size()) return ys[x.val];
    Factorial<Mint> factorial(n - 1);
    vector<Mint> prefix(n + 1, Mint(1));
    for (int i = 0; i < n; ++i) prefix[i + 1] = prefix[i] * (x - Mint(i));
    Mint result = 0, suffix = 1;
    for (int i = n - 1; i >= 0; --i) {
        Mint term = ys[i] * prefix[i] * suffix * factorial.inv_fact(i) * factorial.inv_fact(n - 1 - i);
        if ((n - 1 - i) & 1) result -= term;
        else result += term;
        suffix *= x - Mint(i);
    }
    return result;
}

#endif

/**
 * @brief 連続標本点からの1点評価
 */
