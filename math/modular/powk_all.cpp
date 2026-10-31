#ifndef FIRIEXP_LIBRARY_MATH_POWK_ALL_CPP
#define FIRIEXP_LIBRARY_MATH_POWK_ALL_CPP

#include "modint_base.cpp"

#ifndef FIRIEXP_LIBRARY_MINT_ALIAS_DEFINED
using mint = modint<MOD>;
#define FIRIEXP_LIBRARY_MINT_ALIAS_DEFINED
#endif

#include "../prime/get_min_factor.cpp"
vector<mint> powk_all(int n, ll k) {
    auto min_factor = get_min_factor(n);
    vector<mint> res(n+1);
    res[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if(min_factor[i] == i) res[i] = mint(i).pow(k);
        else res[i] = res[i/min_factor[i]]*res[min_factor[i]];
    }
    return res;
}

#endif
