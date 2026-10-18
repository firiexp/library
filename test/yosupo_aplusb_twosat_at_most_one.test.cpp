#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../graph/twosat.cpp"

bool valid(int mask, int n, const vector<pair<int, int>>& clauses, const vector<vector<int>>& groups) {
    auto value = [&](int literal) { return bool((mask >> (literal % n)) & 1) != (literal >= n); };
    for (auto [a, b] : clauses) if (!value(a) && !value(b)) return false;
    for (const auto& group : groups) {
        int count = 0;
        for (int v : group) count += value(v);
        if (count > 1) return false;
    }
    return true;
}

void check(TwoSAT& sat, const vector<pair<int, int>>& clauses, const vector<vector<int>>& groups) {
    bool possible = false;
    for (int mask = 0; mask < (1 << sat.n); ++mask) possible |= valid(mask, sat.n, clauses, groups);
    auto result = sat.build();
    assert(!result.empty() == possible);
    if (possible) {
        assert((int)result.size() == sat.n);
        int mask = 0;
        for (int i = 0; i < sat.n; ++i) mask |= result[i] << i;
        assert(valid(mask, sat.n, clauses, groups));
    }
    for (int i = 0; i < sat.n; ++i) {
        assert(sat.negate(i) == sat.n + i);
        assert(sat.negate(sat.negate(i)) == i);
    }
    assert(sat.build() == result);
}

void self_check() {
    for (int k = 0, limit = 1; k <= 4; ++k, limit *= 6) {
        for (int code = 0; code < limit; ++code) {
            vector<int> group(k);
            int rest = code;
            for (auto& v : group) { v = rest % 6; rest /= 6; }
            for (int mask = 0; mask < 8; ++mask) {
                TwoSAT sat(3);
                sat.at_most_one(group);
                vector<pair<int, int>> clauses;
                for (int i = 0; i < 3; ++i) {
                    int v = (mask >> i) & 1 ? i : sat.negate(i);
                    clauses.emplace_back(v, v);
                    sat.add_or(v, v);
                }
                check(sat, clauses, {group});
            }
        }
    }
    mt19937 rng(145);
    for (int tc = 0; tc < 1000; ++tc) {
        int n = 1 + rng() % 7;
        TwoSAT sat(n);
        vector<pair<int, int>> clauses;
        vector<vector<int>> groups;
        for (int step = 0; step < 8; ++step) {
            if (rng() % 2) {
                int a = rng() % (2 * n), b = rng() % (2 * n);
                clauses.emplace_back(a, b);
                sat.add_or(a, b);
            } else {
                vector<int> group(rng() % 9);
                for (auto& v : group) v = rng() % (2 * n);
                sat.at_most_one(group);
                groups.push_back(group);
            }
            check(sat, clauses, groups);
        }
    }
}

int main() {
    self_check();
}
