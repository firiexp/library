#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template<class T> constexpr T INF = numeric_limits<T>::max() / 32 * 15 + 208;
#include "../util/fastio.cpp"
#include "../flow/project_selection_problem.cpp"

template<class Score>
void check(ProjectSelectionProblem<ll> &psp, Score score, int fixed = -1) {
    int n = psp.size();
    ll best = LLONG_MIN;
    for (int mask = 0; mask < (1 << n); ++mask)
        if (fixed == -1 || mask == fixed) best = max(best, score(mask));
    for (int repeat = 0; repeat < 2; ++repeat) {
        assert(psp.solve() == best);
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
            check(psp, [&](int mask) { return table[2 * (mask & 1) + ((mask >> 1) & 1)]; }, fixed);
        }
        ProjectSelectionProblem<ll> same(1);
        same.add_pair_profit(0, 0, a, b, c, d);
        check(same, [&](int mask) { return mask ? d : a; });
    }
    mt19937 rng(66);
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
        auto score = [&](int mask) {
            ll sum = 0;
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
            if (i == 3 || i == 7) check(psp, score);
        }
    }
}

int main() {
    self_check();
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
