#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template<class T> constexpr T INF = numeric_limits<T>::max() / 32 * 15 + 208;
#include "../util/fastio.cpp"
#include "../flow/project_selection_problem.cpp"

template<class Score>
void check(ProjectSelectionProblem<ll> &psp, int n, Score score, int fixed = -1) {
    ll best = LLONG_MIN;
    for (int mask = 0; mask < (1 << n); ++mask)
        if (fixed == -1 || mask == fixed) best = max(best, score(mask));
    for (int repeat = 0; repeat < 2; ++repeat) {
        ll value = psp.solve();
        assert(value == best);
        const auto &selected = psp.get_selected();
        int mask = 0;
        for (int i = 0; i < n; ++i) mask |= selected[i] << i;
        assert(fixed == -1 || mask == fixed);
        assert(score(mask) == best);
    }
}

void self_check() {
    for (ll a = -2; a <= 2; ++a) for (ll b = -2; b <= 2; ++b)
    for (ll c = -2; c <= 2; ++c) for (ll d = -2; d <= 2; ++d) {
        if (a + d < b + c) continue;
        array<ll, 4> table{a, b, c, d};
        for (int fixed = -1; fixed < 4; ++fixed) {
            ProjectSelectionProblem<ll> psp(2);
            psp.add_pair_profit(0, 1, a, b, c, d);
            if (fixed != -1) for (int v = 0; v < 2; ++v) {
                if ((fixed >> v) & 1) psp.force_true(v);
                else psp.force_false(v);
            }
            check(psp, 2, [&](int mask) { return table[2 * (mask & 1) + ((mask >> 1) & 1)]; }, fixed);
        }
        ProjectSelectionProblem<ll> same(1);
        same.add_pair_profit(0, 0, a, b, c, d);
        check(same, 1, [&](int mask) { return mask ? d : a; });
    }
    ProjectSelectionProblem<ll> empty;
    empty.add_all_true_profit({}, 3);
    empty.add_all_false_profit({}, 5);
    assert(empty.size() == 0);
    check(empty, 0, [](int) { return 8LL; });

    mt19937 rng(66), group_rng(540);
    for (int tc = 0; tc < 2000; ++tc) {
        int n = 1 + rng() % 6;
        ProjectSelectionProblem<ll> psp(n);
        vector<ll> yes(n), no(n);
        for (int i = 0; i < n; ++i) {
            yes[i] = int(rng() % 11) - 5;
            no[i] = int(rng() % 11) - 5;
            psp.add_true_profit(i, yes[i]);
            psp.add_false_profit(i, no[i]);
        }
        vector<tuple<int, int, array<ll, 4>>> terms;
        vector<ll> group_score(1 << n);
        auto score = [&](int mask) {
            ll sum = group_score[mask];
            for (int i = 0; i < n; ++i) sum += (mask >> i) & 1 ? yes[i] : no[i];
            for (auto [u, v, p] : terms) sum += p[2 * ((mask >> u) & 1) + ((mask >> v) & 1)];
            return sum;
        };
        for (int i = 0; i < 8; ++i) {
            int u = rng() % n, v = rng() % n;
            array<ll, 4> p;
            for (auto &x : p) x = int(rng() % 11) - 5;
            p[3] = max(p[3], p[1] + p[2] - p[0]);
            psp.add_pair_profit(u, v, p[0], p[1], p[2], p[3]);
            terms.emplace_back(u, v, p);
            if (i == 3 || i == 7) check(psp, n, score);
        }
        for (int i = 0; i < 8; ++i) {
            vector<int> vs(group_rng() % (n + 3));
            int members = 0;
            for (int &v : vs) {
                v = group_rng() % n;
                members |= 1 << v;
            }
            ll profit = group_rng() % 6;
            bool all_true = group_rng() % 2;
            int before = psp.size();
            if (all_true) psp.add_all_true_profit(vs, profit);
            else psp.add_all_false_profit(vs, profit);
            assert(psp.size() == before + (profit > 0 && vs.size() > 1));
            for (int mask = 0; mask < (1 << n); ++mask)
                if ((mask & members) == (all_true ? members : 0)) group_score[mask] += profit;
        }
        check(psp, n, score);
        if (tc >= 100) continue;
        for (int fixed = 0; fixed < (1 << n); ++fixed) {
            auto constrained = psp;
            for (int v = 0; v < n; ++v) {
                if (fixed >> v & 1) constrained.force_true(v);
                else constrained.force_false(v);
            }
            check(constrained, n, score, fixed);
        }
    }
}

int main() {
    self_check();
}
