#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
const int MOD = 3;
#include "../util/fastio.cpp"
#include "../math/matrix_rank.cpp"
#include "../math/gauss_jordan_mint.cpp"

int minor_rank(const vector<vector<mint>> &a) {
    int h = a.size(), w = h ? a[0].size() : 0, rank = 0;
    for (int rows = 1; rows < (1 << h); ++rows) {
        int k = __builtin_popcount((unsigned)rows);
        if (k <= rank || k > w) continue;
        vector<int> r;
        for (int i = 0; i < h; ++i) if (rows >> i & 1) r.push_back(i);
        for (int cols = 1; cols < (1 << w); ++cols) {
            if (__builtin_popcount((unsigned)cols) != k) continue;
            vector<int> c, p(k);
            for (int i = 0; i < w; ++i) if (cols >> i & 1) c.push_back(i);
            iota(p.begin(), p.end(), 0);
            mint det = 0;
            do {
                mint term = 1;
                for (int i = 0; i < k; ++i) {
                    term *= a[r[i]][c[p[i]]];
                    for (int j = 0; j < i; ++j) if (p[j] > p[i]) term = -term;
                }
                det += term;
            } while (next_permutation(p.begin(), p.end()));
            if (det != mint(0)) {
                rank = k;
                break;
            }
        }
    }
    return rank;
}

void check(vector<vector<mint>> a, bool independent = true) {
    auto original = a;
    int rank = matrix_rank(a);
    assert(a == original);
    if (independent) assert(rank == minor_rank(a));
    if (!a.empty()) assert(rank == gauss_jordan(a));
    assert(rank == matrix_rank(std::move(original)));
}

void self_check() {
    check({});
    check({{}, {}, {}});
    check({{0, 0, 0}, {0, 0, 0}});
    check({{0, 1}, {1, 0}});
    check({{0, 0, 1, 0, 2}, {0, 0, 2, 0, 1}, {0, 0, 0, 0, 1}});
    mt19937 random(218);
    for (int tc = 0; tc < 1000; ++tc) {
        int h = random() % 6, w = random() % 6;
        vector<vector<mint>> a(h, vector<mint>(w));
        for (auto &row : a) for (auto &x : row) x = random() % MOD;
        if (tc % 3 == 0 && h > 1) a.back() = a.front();
        if (tc % 5 == 0) for (auto &row : a) for (int j = 0; j < w; j += 2) row[j] = 0;
        check(a);
    }
    for (int tc = 0; tc < 300; ++tc) {
        int h = 1 + random() % 30, w = random() % 30;
        vector<vector<mint>> a(h, vector<mint>(w));
        for (auto &row : a) for (auto &x : row) x = random() % MOD;
        check(a, false);
    }
}

int main() {
    self_check();
    Scanner in;
    Printer out;
    int a, b;
    in.read(a, b);
    out.println(a + b);
}
