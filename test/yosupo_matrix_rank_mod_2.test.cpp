#define PROBLEM "https://judge.yosupo.jp/problem/matrix_rank_mod_2"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../math/linear_algebra/matrix_mod2.cpp"

int main() {
    Scanner in;
    Printer out;
    int n, m;
    in.read(n, m);
    bool transpose = n > m;
    vector<DynamicBitset> a(min(n, m), DynamicBitset(max(n, m)));
    string s;
    for (int i = 0; i < n && m > 0; ++i) {
        in.read(s);
        for (int j = 0; j < m; ++j) {
            if (s[j] != '1') continue;
            if (transpose) a[j].set(i);
            else a[i].set(j);
        }
    }
    out.println(matrix_rank_mod2(std::move(a)));
}
