#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
static const int MOD = 998244353;

#include "../util/fastio.cpp"
#include "../util/modint.cpp"
#include "../math/comb_table.cpp"

int main() {
    // Multiplicative formula, independent of the table's Pascal recurrence.
    for (int n = 0; n <= 40; ++n) {
        for (int m = 0; m <= 45; ++m) {
            auto c = comb_table(n, m);
            assert(int(c.size()) == n + 1);
            for (int i = 0; i <= n; ++i) {
                assert(int(c[i].size()) == m + 1);
                mint expected = 1;
                for (int j = 0; j <= m; ++j) {
                    if (j > 0) expected = j <= i ? expected * mint(i - j + 1) / mint(j) : mint(0);
                    assert(c[i][j] == expected);
                }
            }
        }
    }
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
