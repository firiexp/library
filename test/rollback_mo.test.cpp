#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../util/rollback_mo.cpp"
#include "../util/mo.cpp"
#include "../util/rollback_mo.cpp"

struct DistanceState {
    struct Change { int value, first, last, best; };
    const vector<int> &a;
    vector<int> first, last;
    vector<Change> history;
    vector<int> answers, calls;
    int best = 0, resets = 0;

    DistanceState(const vector<int> &a, int q)
        : a(a), first(8, -1), last(8, -1), answers(q, -1), calls(q) {}

    void add(int i) {
        int v = a[i];
        history.push_back({v, first[v], last[v], best});
        if (first[v] == -1) first[v] = last[v] = i;
        else {
            first[v] = min(first[v], i);
            last[v] = max(last[v], i);
        }
        best = max(best, last[v] - first[v]);
    }

    void rollback(size_t token) {
        while (history.size() > token) {
            auto c = history.back();
            history.pop_back();
            first[c.value] = c.first;
            last[c.value] = c.last;
            best = c.best;
        }
    }

    void reset() { rollback(0); ++resets; }
    void add_left(int i) { add(i); }
    void add_right(int i) { add(i); }
    size_t snapshot() const { return history.size(); }
    void output(int id) { answers[id] = best; ++calls[id]; }
};

struct OrderedState {
    deque<int> order;
    vector<bool> side;
    vector<pair<int, int>> range;

    explicit OrderedState(const vector<Query> &queries) : range(queries.size()) {
        for (const auto &q : queries) range[q.no] = {q.l, q.r};
    }

    void rollback(size_t token) {
        while (side.size() > token) {
            if (side.back()) order.pop_front();
            else order.pop_back();
            side.pop_back();
        }
    }

    void reset() { rollback(0); }
    size_t snapshot() const { return side.size(); }

    void add_left(int i) {
        assert(order.empty() || i + 1 == order.front());
        order.push_front(i);
        side.push_back(true);
    }

    void add_right(int i) {
        assert(order.empty() || order.back() + 1 == i);
        order.push_back(i);
        side.push_back(false);
    }

    void output(int id) const {
        auto [l, r] = range[id];
        assert((int)order.size() == r - l);
        for (int i = l; i < r; ++i) assert(order[i - l] == i);
    }
};

void check(const vector<int> &a, const vector<Query> &queries, int width) {
    DistanceState state(a, queries.size());
    rollback_mo_solve(a.size(), queries, state, width);
    assert(state.history.empty() && state.best == 0);
    assert(queries.empty() ? state.resets == 0 : state.resets >= 2);
    for (const auto &q : queries) {
        int expected = 0;
        for (int i = q.l; i < q.r; ++i) {
            for (int j = i + 1; j < q.r; ++j) {
                if (a[i] == a[j]) expected = max(expected, j - i);
            }
        }
        assert(state.calls[q.no] == 1 && state.answers[q.no] == expected);
    }

    OrderedState ordered(queries);
    rollback_mo_solve(a.size(), queries, ordered, width);
    assert(ordered.order.empty() && ordered.side.empty());
}

int main() {
    check({}, {}, 0);
    check({}, {{0, 0, 0}}, 0);
    mt19937 rng(315);
    for (int n = 0; n <= 30; ++n) {
        vector<int> a(n);
        for (int &v : a) v = rng() % 8;
        vector<Query> queries;
        for (int l = 0; l <= n; ++l) {
            for (int r = l; r <= n; ++r) queries.emplace_back(l, r, queries.size());
        }
        shuffle(queries.begin(), queries.end(), rng);
        for (int width : {0, 1, 2, 7, n + 1, INT_MAX}) check(a, queries, width);
    }
    for (int trial = 0; trial < 300; ++trial) {
        int n = rng() % 60;
        vector<int> a(n);
        for (int &v : a) v = rng() % 8;
        vector<Query> queries;
        int q = rng() % 100;
        for (int id = 0; id < q; ++id) {
            int l = rng() % (n + 1), r = rng() % (n + 1);
            if (l > r) swap(l, r);
            queries.emplace_back(l, r, id);
        }
        check(a, queries, rng() % 20);
    }
}
