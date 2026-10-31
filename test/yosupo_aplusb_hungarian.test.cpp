#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../graph/matching/hungarian.cpp"

template<class T, bool Minimize>
void check(const vector<vector<T>> &cost, bool brute = true) {
    using Wide = conditional_t<is_integral<T>::value, __int128, long double>;
    auto copy = cost;
    auto [answer, match, row, col] = hungarian<T, Minimize>(cost);
    assert(cost == copy);
    int n = cost.size(), m = n ? cost[0].size() : 0;
    assert((int)match.size() == n && (int)row.size() == n && (int)col.size() == m);
    auto equal = [&](Wide a, Wide b) {
        if constexpr (is_integral<T>::value) return a == b;
        else return abs(a - b) <= 1e-9L * max({1.0L, abs(a), abs(b)});
    };
    Wide primal = 0, dual = 0;
    vector<bool> used(m);
    for (int i = 0; i < n; ++i) {
        assert(0 <= match[i] && match[i] < m && !used[match[i]]);
        used[match[i]] = true;
        primal += cost[i][match[i]];
        dual += row[i];
        for (int j = 0; j < m; ++j) {
            Wide sum = Wide(row[i]) + col[j];
            assert(equal(sum, cost[i][j]) || (Minimize ? sum < cost[i][j] : sum > cost[i][j]));
        }
        assert(equal(Wide(row[i]) + col[match[i]], cost[i][match[i]]));
    }
    for (int j = 0; j < m; ++j) {
        dual += col[j];
        assert(equal(col[j], 0) || (Minimize ? col[j] < 0 : col[j] > 0));
        if (!used[j]) assert(equal(col[j], 0));
    }
    assert(equal(primal, answer) && equal(dual, answer));
    if (!brute) return;
    fill(used.begin(), used.end(), false);
    optional<Wide> best;
    auto dfs = [&](auto &&self, int i, Wide sum) -> void {
        if (i == n) {
            if (!best || (Minimize ? sum < *best : sum > *best)) best = sum;
            return;
        }
        for (int j = 0; j < m; ++j) if (!used[j]) {
            used[j] = true;
            self(self, i + 1, sum + cost[i][j]);
            used[j] = false;
        }
    };
    dfs(dfs, 0, 0);
    assert(equal(*best, answer));
}

template<class T>
void both(const vector<vector<T>> &cost, bool brute = true) {
    check<T, true>(cost, brute);
    check<T, false>(cost, brute);
}

int main() {
    both<long long>({});
    both<long long>({{LLONG_MIN}});
    both<long long>({{LLONG_MAX}});
    both<long long>({{LLONG_MIN, LLONG_MAX}});
    both<long long>({{LLONG_MAX, LLONG_MAX - 1}, {-LLONG_MAX, -LLONG_MAX + 1}});
    both<long long>({{LLONG_MIN, LLONG_MIN + 1}, {LLONG_MAX, LLONG_MAX - 1}});
    both<int>({{INT_MAX, INT_MAX - 1}, {-INT_MAX, -INT_MAX + 1}});
    both<double>({{0.1, -0.2, 0.3}, {-0.4, 0.5, -0.6}});
    const long long bound = 2000000000000000000LL;
    for (int sign : {-1, 1}) {
        vector<vector<long long>> cost(10, vector<long long>(10));
        for (int i = 0; i < 10; ++i) {
            fill(cost[i].begin(), cost[i].end(), (i < 5 ? bound : -bound) * sign);
        }
        both(cost, false);
    }
    mt19937 rng(240);
    for (int trial = 0; trial < 200; ++trial) {
        int n = 1 + rng() % 4, m = n + rng() % 3;
        vector<vector<long long>> cost(n, vector<long long>(m));
        const long long values[] = {-bound, -bound + 1, 0, bound - 1, bound};
        for (auto &row : cost) for (auto &x : row) x = values[rng() % 5];
        both(cost);
    }
    for (int trial = 0; trial < 100; ++trial) {
        long long scale = LLONG_MAX / 48 + trial % 2;
        vector<vector<long long>> cost(5, vector<long long>(7));
        for (auto &row : cost) for (auto &x : row) x = (int(rng() % 3) - 1) * scale;
        both(cost);
    }
    for (int trial = 0; trial < 4000; ++trial) {
        int n = rng() % 6, m = n + rng() % 3;
        vector<vector<long long>> cost(n, vector<long long>(m));
        for (auto &row : cost) for (auto &x : row) x = int(rng() % 41) - 20;
        both(cost);
        if (trial < 200) {
            vector<vector<double>> real(n, vector<double>(m));
            for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) real[i][j] = cost[i][j] / 7.0;
            both(real);
        }
    }
    for (int n : {1, 4, 100}) for (int m : {n, n + 10}) {
        both(vector<vector<long long>>(n, vector<long long>(m, -7)), n <= 4);
        vector<vector<long long>> cost(n, vector<long long>(m));
        for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) cost[i][j] = i * j;
        both(cost, n <= 4);
    }
}
