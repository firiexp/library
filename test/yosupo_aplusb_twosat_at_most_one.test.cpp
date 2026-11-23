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
    TwoSAT empty(0);
    empty.at_most_one({});
    assert(empty.build().empty());
    {
        TwoSAT sat(4);
        sat.at_most_one({2});
        sat.at_most_one({{2, false}});
        assert(sat.scc.n == 8 && sat.scc.edges.empty());
        sat.at_most_one({0, sat.negate(1), 2});
        sat.at_most_one({{2, false}, {3, true}, {0, true}});
        check(sat, {}, {{0, 5, 2}, {6, 3, 0}});
    }
    {
        TwoSAT sat(2);
        sat.at_most_one({{}, {}});
        vector<int> ids{sat.negate(0), 1};
        sat.at_most_one({ids.begin(), ids.end()});
        assert(sat.build() == vector<int>({0, 0}));
    }
    for (int f = 0; f < 2; ++f) for (int g = 0; g < 2; ++g) {
        for (int j = 0; j < 2; ++j) for (int mask = 0; mask < 4; ++mask) {
            TwoSAT sat(2);
            sat.add_clause(0, f, j, g);
            vector<pair<int, int>> clauses{{f ? 0 : 2, g ? j : j + 2}};
            for (int i = 0; i < 2; ++i) {
                bool value = (mask >> i) & 1;
                sat.fix(i, value);
                int literal = value ? i : i + 2;
                clauses.emplace_back(literal, literal);
            }
            check(sat, clauses, {});
        }
    }
    for (bool value : {false, true}) {
        TwoSAT sat(3);
        vector<vector<int>> groups{{0, 1, 2}};
        sat.at_most_one(groups[0]);
        sat.fix(0, value);
        int literal = value ? 0 : 3;
        vector<pair<int, int>> clauses{{literal, literal}};
        check(sat, clauses, groups);
        sat.fix(0, !value);
        clauses.emplace_back(sat.negate(literal), sat.negate(literal));
        check(sat, clauses, groups);
    }
    for (int k = 0, limit = 1; k <= 4; ++k, limit *= 6) {
        for (int code = 0; code < limit; ++code) {
            vector<int> group(k);
            int rest = code;
            for (auto& v : group) { v = rest % 6; rest /= 6; }
            vector<pair<int, bool>> literals;
            for (int v : group) literals.emplace_back(v % 3, v < 3);
            for (int mask = 0; mask < 8; ++mask) {
                TwoSAT sat(3);
                sat.at_most_one(group);
                TwoSAT pairs(3);
                pairs.at_most_one(literals);
                assert(pairs.scc.n == 6 + (k > 2 ? 2 * (k - 1) : 0));
                vector<pair<int, int>> clauses;
                for (int i = 0; i < 3; ++i) {
                    int v = (mask >> i) & 1 ? i : sat.negate(i);
                    clauses.emplace_back(v, v);
                    sat.add_or(v, v);
                    pairs.fix(i, (mask >> i) & 1);
                }
                check(sat, clauses, {group});
                int count = 0;
                for (auto [i, value] : literals) count += bool((mask >> i) & 1) == value;
                assert(!pairs.build().empty() == (count <= 1));
            }
        }
    }
    mt19937 rng(145);
    for (int tc = 0; tc < 2500; ++tc) {
        int n = 1 + rng() % 8;
        TwoSAT sat(n);
        vector<pair<int, int>> clauses;
        vector<vector<int>> groups;
        for (int step = 0; step < 8; ++step) {
            int mode = rng() % 5;
            if (mode == 0) {
                int a = rng() % (2 * n), b = rng() % (2 * n);
                clauses.emplace_back(a, b);
                sat.add_or(a, b);
            } else if (mode == 1) {
                vector<int> group(rng() % 9);
                for (auto& v : group) v = rng() % (2 * n);
                if (rng() % 2) {
                    vector<pair<int, bool>> literals;
                    for (int v : group) literals.emplace_back(v % n, v < n);
                    sat.at_most_one(literals);
                } else {
                    sat.at_most_one(group);
                }
                groups.push_back(group);
            } else if (mode == 2) {
                int a = rng() % (2 * n), b = rng() % (2 * n);
                sat.add_if(a, b);
                clauses.emplace_back(sat.negate(a), b);
            } else {
                int i = rng() % n, j = rng() % n;
                bool f = rng() % 2, g = rng() % 2;
                if (mode == 3) sat.add_clause(i, f, j, g);
                else {
                    sat.fix(i, f);
                    j = i;
                    g = f;
                }
                clauses.emplace_back(f ? i : i + n, g ? j : j + n);
            }
            check(sat, clauses, groups);
        }
    }
}

int main() {
    self_check();
}
