#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det_arbitrary_mod"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
#include "../util/fastio.cpp"
#include "../util/modint_arbitrary.cpp"
#include "../math/matrix_determinant_mod.cpp"

int main() {
    Scanner in;
    Printer out;
    int n, mod;
    in.read(n, mod);
    mint::set_mod(mod);
    vector<vector<mint>> a(n, vector<mint>(n));
    for (auto& row : a) for (auto& x : row) {
        ll value;
        in.read(value);
        x = value;
    }
    out.println(matrix_determinant_mod(a).value());
}
