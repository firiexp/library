#include "../util/modint.cpp"

#include "./get_min_factor.cpp"
vector<mint> powk_all(int n, ll k) {
    auto min_factor = get_min_factor(n);
    vector<mint> res(n+1);
    res[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if(min_factor[i] == i) res[i] = mint(i).pow(k);
        else res[i] = res[i/min_factor[i]]*res[i];
    }
    return res;
}