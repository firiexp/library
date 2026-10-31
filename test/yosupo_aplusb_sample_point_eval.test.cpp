#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
const int MOD = 1000000007;
#include "../util/fastio.cpp"
#include "../math/combinatorics/factorial.cpp"
#include "../fps/sample_point_eval.cpp"
#include "../math/combinatorics/factorial.cpp"

template <class Mint>
Mint evaluate(const vector<Mint>& f, Mint x) {
    Mint result = 0;
    for (int i = (int)f.size() - 1; i >= 0; --i) result = result * x + f[i];
    return result;
}

template <unsigned P>
void check_mod() {
    using Mint = modint<P>;
    mt19937 rng(P);
    assert(sample_point_eval(vector<Mint>{}, Mint(P - 1)) == Mint(0));
    for (int tc = 0; tc < 300; ++tc) {
        int n = tc == 0 ? min(P, 70U) : 1 + rng() % min(P, 70U);
        vector<Mint> f(n), ys(n);
        for (auto& c : f) c = rng() % P;
        if (tc == 1) fill(f.begin(), f.end(), Mint(0));
        for (int i = 0; i < n; ++i) ys[i] = evaluate(f, Mint(i));
        auto original = ys;
        for (int i = 0; i < n; ++i) assert(sample_point_eval(ys, Mint(i)) == ys[i]);
        for (int i = 0; i < 12; ++i) {
            Mint x = i == 0 ? Mint(P - 1) : i == 1 ? Mint(n) : Mint(rng() % P);
            assert(sample_point_eval(ys, x) == evaluate(f, x));
        }
        assert(ys == original);
        Factorial<Mint> factorial(n - 1);
        assert(factorial.fact(n - 1) * factorial.inv_fact(n - 1) == Mint(1));
    }
}

int main() {
    check_mod<2>();
    check_mod<3>();
    check_mod<5>();
    check_mod<17>();
    check_mod<998244353>();
    check_mod<1000000007>();
}
