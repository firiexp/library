#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det_arbitrary_mod"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include "../util/fastio.cpp"
#include "../math/matrix_determinant_mod.cpp"

int main() {
    Scanner in;
    Printer out;
    int n, mod;
    in.read(n, mod);
    vector<vector<ll>> a(n, vector<ll>(n));
    for (auto& row : a) for (auto& x : row) in.read(x);
    out.println(matrix_determinant_mod(a, mod));
}
