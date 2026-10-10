#define PROBLEM "https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;

#include "../util/fastio.cpp"
#include "../math/ntt.cpp"
#include "../math/fastkitamasa.cpp"
#include "fastkitamasa_self_check.cpp"

int main() {
    fastkitamasa_test::self_check();
    Scanner in;
    Printer out;
    int d;
    long long n;
    in.read(d, n);
    vector<mint> a(d), f(d + 1);
    for (auto &x : a) {
        int value;
        in.read(value);
        x = value;
    }
    for (int i = 0; i < d; ++i) {
        int value;
        in.read(value);
        f[d - 1 - i] = -mint(value);
    }
    f[d] = 1;
    auto coefficients = Fast_Kitamasa(f).kitamasa(n);
    mint answer = 0;
    for (int i = 0; i < d; ++i) answer += coefficients[i] * a[i];
    out.println(answer.val);
}
