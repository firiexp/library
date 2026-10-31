#define PROBLEM "https://judge.yosupo.jp/problem/binomial_coefficient"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
#include "../util/fastio.cpp"
#include "../math/combinatorics/binom_mod.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int t;
    ll mod;
    sc.read(t, mod);
    const BinomMod binom(mod);
    while (t--) {
        ll n, k;
        sc.read(n, k);
        pr.println(binom.C(n, k));
    }
}
