#define PROBLEM "https://judge.yosupo.jp/problem/matrix_product_mod_2"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../math/linear_algebra/matrix_mod2.cpp"

int main() {
    Scanner in;
    Printer out;
    int n, m, k;
    in.read(n, m, k);
    auto read_matrix = [&](int h, int w) {
        vector<DynamicBitset> matrix(h, DynamicBitset(w));
        string s;
        for (auto &row : matrix) {
            in.read(s);
            for (int j = 0; j < w; ++j) if (s[j] == '1') row.set(j);
        }
        return matrix;
    };
    auto a = read_matrix(n, m);
    auto b = read_matrix(m, k);
    for (const auto &row : matrix_product_mod2(a, b)) {
        for (int j = 0; j < k; ++j) out.print(row.test(j) ? '1' : '0');
        out.println();
    }
}
