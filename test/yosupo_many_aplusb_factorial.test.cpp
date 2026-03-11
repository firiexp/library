#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb"

#include <vector>
using namespace std;

using ll = long long;
using uint = unsigned;
using ull = unsigned long long;

static constexpr int MOD = 998244353;

#include "../util/fastio.cpp"
#include "../math/factorial.cpp"

vector<vector<mint>> build_comb(int n) {
    vector<vector<mint>> comb(n + 1, vector<mint>(n + 1));
    comb[0][0] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            comb[i + 1][j] += comb[i][j];
            comb[i + 1][j + 1] += comb[i][j];
        }
    }
    return comb;
}

mint brute_perm(int n, int k) {
    if (n < 0 || k < 0 || n < k) return 0;
    mint res = 1;
    for (int i = 0; i < k; ++i) res *= n - i;
    return res;
}

mint brute_homo(const vector<vector<mint>> &comb, int n, int k) {
    if (n < 0 || k < 0) return 0;
    if (k == 0) return 1;
    if (n == 0) return 0;
    return comb[n + k - 1][k];
}

int main() {
    {
        Factorial f;
        Factorial g;
        auto comb = build_comb(80);
        if (f.max_n() != 0) return 1;
        if (g.max_n() != 0) return 1;
        if (f.fact(0) != 1 || f.inv_fact(0) != 1 || f[0] != 1) return 1;
        for (int n = 0; n <= 30; ++n) {
            if (n > 0 && f.inv(n) * mint(n) != 1) return 1;
            if (f.fact(n) * f.inv_fact(n) != 1) return 1;
            if (f[-n] != f.inv_fact(n)) return 1;
            if (f.max_n() < n) return 1;
            for (int k = 0; k <= 30; ++k) {
                mint want_c = (k <= n ? comb[n][k] : mint(0));
                if (f.C(n, k) != want_c) return 1;
                if (f.P(n, k) != brute_perm(n, k)) return 1;
                if (f.H(n, k) != brute_homo(comb, n, k)) return 1;
            }
        }
        if (f.C(-1, 0) != 0 || f.C(3, -1) != 0 || f.C(3, 4) != 0) return 1;
        if (f.P(-1, 0) != 0 || f.P(3, -1) != 0 || f.P(3, 4) != 0) return 1;
        if (f.H(-1, 0) != 0 || f.H(3, -1) != 0 || f.H(0, 3) != 0) return 1;
        if (f.inv(-1) != 0) return 1;
        if (f.inv_fact(-1) != 0) return 1;
        f.ensure(100);
        if (f.max_n() < 100) return 1;
        if (g.max_n() < 100) return 1;
    }

    Scanner sc;
    Printer pr;
    int t;
    sc.read(t);
    while (t--) {
        ll a, b;
        sc.read(a, b);
        pr.writeln(a + b);
    }
    return 0;
}
