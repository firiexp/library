#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../flow/hungarian.cpp"

void self_check() {
    mt19937 rng(115);
    for (int n = 0; n <= 8; ++n) {
        for (int tc = 0; tc < 100; ++tc) {
            vector<vector<long long>> a(n, vector<long long>(n));
            for (auto &row : a) for (auto &x : row) x = int(rng() % 101) - 50;
            auto [ans, match, row, col] = hungarian<long long>(a);
            long long dual_sum = accumulate(row.begin(), row.end(), 0LL)
                               + accumulate(col.begin(), col.end(), 0LL);
            assert(dual_sum == ans);
            long long primal_sum = 0;
            vector<bool> used(n);
            for (int i = 0; i < n; ++i) {
                assert(0 <= match[i] && match[i] < n && !used[match[i]]);
                used[match[i]] = true;
                primal_sum += a[i][match[i]];
                for (int j = 0; j < n; ++j) assert(row[i] + col[j] <= a[i][j]);
            }
            assert(primal_sum == ans);
        }
    }
}

int main() {
    self_check();
}
