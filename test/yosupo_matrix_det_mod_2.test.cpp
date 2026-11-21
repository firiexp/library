#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det_mod_2"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../math/linear_algebra/matrix_determinant_mod2.cpp"

int main() {
    Scanner in;
    Printer out;
    int n;
    in.read(n);
    vector<DynamicBitset> a(n, DynamicBitset(n));
    string s;
    for (auto &row : a) {
        in.read(s);
        for (int j = 0; j < n; ++j) if (s[j] == '1') row.set(j);
    }
    out.println(matrix_determinant_mod2(std::move(a)));
}
