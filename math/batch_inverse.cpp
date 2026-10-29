#ifndef FIRIEXP_LIBRARY_MATH_BATCH_INVERSE_CPP
#define FIRIEXP_LIBRARY_MATH_BATCH_INVERSE_CPP

#include "../util/modint_base.cpp"

template<class Mint>
vector<Mint> batch_inverse(const vector<Mint>& a) {
    if (a.empty()) return {};
    vector<Mint> result(a.size());
    Mint product = 1;
    for (size_t i = 0; i < a.size(); ++i) {
        result[i] = product;
        product *= a[i];
    }
    assert(product != Mint(0));
    Mint inverse = product.inv();
    for (size_t i = a.size(); i-- > 0;) {
        result[i] *= inverse;
        inverse *= a[i];
    }
    return result;
}

#endif

/**
 * @brief 配列内の全ての要素の逆元
 */
