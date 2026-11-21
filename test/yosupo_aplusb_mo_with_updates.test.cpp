#define STANDALONE

#include <bits/stdc++.h>
using namespace std;

#include "../util/mo_with_updates.cpp"

struct Moves {
    int apply_inside = 0, apply_outside = 0, undo_inside = 0, undo_outside = 0;
};

Moves check(const vector<int> &initial, const vector<pair<int, int>> &updates,
            const vector<MoUpdateQuery> &queries, int width, mt19937 &rng) {
    if (queries.empty()) {
        auto unexpected = [](auto...) { assert(false); };
        mo_with_updates_solve((int)initial.size(), queries, unexpected, unexpected,
                              unexpected, unexpected, unexpected, unexpected, unexpected, width);
        return {};
    }
    vector<vector<int>> history{initial};
    vector<int> before;
    for (auto [pos, value] : updates) {
        before.push_back(history.back()[pos]);
        auto next = history.back();
        next[pos] = value;
        history.push_back(std::move(next));
    }
    auto shuffled = queries;
    shuffle(shuffled.begin(), shuffled.end(), rng);
    vector<int> a = initial, seen(queries.size());
    array<int, 8> freq{};
    int l = 0, r = 0, t = 0;
    Moves moves;
    auto assign = [&](int k, int left, int right, int from, int to) {
        int pos = updates[k].first;
        assert(left == l && right == r && a[pos] == from);
        if (l <= pos && pos < r) {
            --freq[from];
            ++freq[to];
        }
        a[pos] = to;
        return l <= pos && pos < r;
    };
    auto apply = [&](int k, int left, int right) {
        assert(k == t && k < (int)updates.size());
        ++t;
        if (assign(k, left, right, before[k], updates[k].second)) ++moves.apply_inside;
        else ++moves.apply_outside;
    };
    auto undo = [&](int k, int left, int right) {
        --t;
        assert(k == t && k >= 0);
        if (assign(k, left, right, updates[k].second, before[k])) ++moves.undo_inside;
        else ++moves.undo_outside;
    };
    auto add_left = [&](int i) {
        assert(i == l - 1);
        --l;
        ++freq[a[i]];
    };
    auto add_right = [&](int i) {
        assert(i == r);
        ++r;
        ++freq[a[i]];
    };
    auto erase_left = [&](int i) {
        assert(i == l && l < r);
        ++l;
        --freq[a[i]];
    };
    auto erase_right = [&](int i) {
        assert(i == r - 1 && l < r);
        --r;
        --freq[a[i]];
    };
    auto output = [&](int no) {
        int id = -1 - no;
        assert(0 <= id && id < (int)queries.size());
        const auto &q = queries[id];
        assert(q.no == no && q.l == l && q.r == r && q.t == t);
        assert(a == history[t]);
        array<int, 8> expected{};
        for (int i = q.l; i < q.r; ++i) ++expected[history[q.t][i]];
        assert(freq == expected);
        ++seen[id];
    };
    mo_with_updates_solve((int)a.size(), shuffled, add_left, add_right, erase_left, erase_right,
                          apply, undo, output, width);
    for (int count : seen) assert(count == 1);
    return moves;
}

int main() {
    mt19937 rng(551);
    check({}, {}, {}, 0, rng);
    check({}, {}, {{0, 0, 0, -1}}, 0, rng);
    check({2}, {{0, 4}}, {}, 0, rng);
    check({2, 3}, {}, {{0, 0, 0, -1}, {0, 2, 0, -2}, {2, 2, 0, -3}}, 0, rng);
    Moves moves = check({0, 1, 2, 3}, {{0, 4}, {3, 5}, {0, 6}, {0, 6}},
                        {{0, 3, 0, -1}, {0, 3, 4, -2}, {1, 4, 4, -3}}, 1, rng);
    assert(moves.apply_inside && moves.apply_outside && moves.undo_inside && moves.undo_outside);

    for (int trial = 0; trial < 2000; ++trial) {
        int n = rng() % 33, u = n ? rng() % 33 : 0, q = rng() % 41;
        vector<int> initial(n);
        for (int &x : initial) x = rng() % 8;
        vector<pair<int, int>> updates;
        for (int i = 0; i < u; ++i) updates.emplace_back(rng() % n, rng() % 8);
        vector<MoUpdateQuery> queries;
        for (int i = 0; i < q; ++i) {
            int l = rng() % (n + 1), r = rng() % (n + 1);
            if (l > r) swap(l, r);
            queries.emplace_back(l, r, rng() % (u + 1), -1 - i);
        }
        const int widths[] = {0, -1, 1, 5, INT_MAX};
        check(initial, updates, queries, widths[trial % 5], rng);
    }
}
