#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb"

#include <algorithm>
#include <random>
#include <utility>
#include <vector>
using namespace std;

#include "../util/fastio.cpp"
#include "../graph/bipartite_matching.cpp"

int main() {
    {
        mt19937 rng(123456789);
        for (int l = 0; l <= 8; ++l) {
            for (int r = 0; r <= 8; ++r) {
                for (int trial = 0; trial < 200; ++trial) {
                    vector<vector<int>> g(l);
                    for (int i = 0; i < l; ++i) {
                        for (int j = 0; j < r; ++j) {
                            if (uniform_int_distribution<int>(0, 1)(rng)) g[i].push_back(j);
                        }
                    }

                    Bipartite_Matching bm(l, r);
                    for (int i = 0; i < l; ++i) {
                        for (int j : g[i]) bm.add_edge(i, j);
                    }
                    int got = bm.matching();

                    vector<int> dp(1 << r, -1);
                    dp[0] = 0;
                    for (int i = 0; i < l; ++i) {
                        auto ndp = dp;
                        for (int mask = 0; mask < (1 << r); ++mask) {
                            if (dp[mask] < 0) continue;
                            for (int j : g[i]) {
                                if (mask >> j & 1) continue;
                                ndp[mask | (1 << j)] = max(ndp[mask | (1 << j)], dp[mask] + 1);
                            }
                        }
                        dp.swap(ndp);
                    }
                    int want = 0;
                    for (int x : dp) want = max(want, x);
                    if (got != want) return 1;

                    auto pairs = bm.get_pairs();
                    if ((int)pairs.size() != got) return 1;
                    vector<int> used_l(l, 0), used_r(r, 0);
                    for (auto &&[a, b] : pairs) {
                        if (!(0 <= a && a < l && 0 <= b && b < r)) return 1;
                        if (used_l[a] || used_r[b]) return 1;
                        used_l[a] = used_r[b] = 1;
                        if (bm.match[a] != b + l) return 1;
                        if (bm.match[b + l] != a) return 1;
                        if (find(g[a].begin(), g[a].end(), b) == g[a].end()) return 1;
                    }
                }
            }
        }
    }

    Scanner sc;
    Printer pr;
    int t;
    sc.read(t);
    while (t--) {
        long long a, b;
        sc.read(a, b);
        pr.writeln(a + b);
    }
    return 0;
}
