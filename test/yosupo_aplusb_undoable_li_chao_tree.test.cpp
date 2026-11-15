#define STANDALONE

#include <bits/stdc++.h>
using namespace std;

#include "../datastructure/undoable_li_chao_tree.cpp"
#include "../util/offline_time_intervals.cpp"

struct TestLine {
    long long a, b;
    int id;
};

optional<pair<long long, int>> naive(const vector<TestLine> &lines, long long x) {
    optional<pair<long long, int>> result;
    for (auto [a, b, id] : lines) {
        auto value = make_pair(a * x + b, id);
        if (!result || value < *result) result = value;
    }
    return result;
}

void check(const UndoableLiChaoTree<long long> &tree, const vector<long long> &xs,
           const vector<TestLine> &lines) {
    for (long long x = -22; x <= 22; ++x) {
        bool registered = find(xs.begin(), xs.end(), x) != xs.end();
        assert(tree.query_with_id(x) == (registered ? naive(lines, x) : nullopt));
    }
}

void random_branches() {
    mt19937 rng(412);
    for (int trial = 0; trial < 250; ++trial) {
        vector<long long> xs(rng() % 60);
        for (auto &x : xs) x = int(rng() % 41) - 20;
        UndoableLiChaoTree<long long> tree(xs);
        vector<TestLine> lines;
        vector<pair<size_t, size_t>> states{ {tree.snapshot(), 0}};
        for (int step = 0; step < 400; ++step) {
            int type = rng() % 5;
            if (type < 3) {
                TestLine line{int(rng() % 21) - 10, int(rng() % 41) - 20, int(rng() % 1000)};
                if (!lines.empty() && rng() % 4 == 0) {
                    line.a = lines.back().a;
                    line.b = lines.back().b;
                }
                tree.add_line(line.a, line.b, line.id);
                lines.push_back(line);
            } else if (type == 3) {
                states.push_back({tree.snapshot(), lines.size()});
            } else {
                int index = rng() % states.size();
                tree.rollback(states[index].first);
                lines.resize(states[index].second);
                states.resize(index + 1);
            }
            auto state = tree.snapshot();
            check(tree, xs, lines);
            assert(tree.snapshot() == state);
        }
        tree.rollback(0);
        check(tree, xs, {});
    }
}

void offline_intervals() {
    mt19937 rng(1412);
    for (int trial = 0; trial < 300; ++trial) {
        int q = rng() % 60;
        vector<long long> xs{-20, -5, 0, 1, 17, 20};
        UndoableLiChaoTree<long long> tree(xs);
        vector<TestLine> base;
        if (trial % 2) {
            base.push_back({0, 10, 5000});
            tree.add_line(0, 10, 5000);
        }
        auto state = tree.snapshot();
        vector<TestLine> lines;
        vector<pair<int, int>> intervals;
        OfflineTimeIntervals times(q);
        for (int i = 0; i < 50; ++i) {
            lines.push_back({int(rng() % 11) - 5, int(rng() % 21) - 10, 1000 - i});
            int l = rng() % (q + 1), r = rng() % (q + 1);
            if (l > r) swap(l, r);
            intervals.push_back({l, r});
            times.add_interval(l, r, i);
        }
        for (int run = 0; run < 2; ++run) {
            int answered = 0;
            times.run([&] { return tree.snapshot(); },
                [&](int event) {
                    auto [a, b, id] = lines[event];
                    tree.add_line(a, b, id);
                },
                [&](size_t token) { tree.rollback(token); },
                [&](int time) {
                    assert(time == answered++);
                    auto active = base;
                    for (int i = 0; i < (int)lines.size(); ++i) {
                        auto [l, r] = intervals[i];
                        if (l <= time && time < r) active.push_back(lines[i]);
                    }
                    check(tree, xs, active);
                });
            assert(answered == q && tree.snapshot() == state);
            check(tree, xs, base);
        }
    }
}

int main() {
    random_branches();
    offline_intervals();
    UndoableLiChaoTree<long long> single({3, 3});
    single.add_line(1, 0, INT_MAX);
    auto state = single.snapshot();
    single.add_line(-1, 6, 0);
    assert(single.query_with_id(3) == make_pair(3LL, 0));
    single.rollback(state);
    assert(single.query_with_id(3) == make_pair(3LL, INT_MAX));
    single.rollback(0);
    assert(!single.query_with_id(3));
    const __int128 large = 1000000000000000000LL;
    UndoableLiChaoTree<__int128> wide({-large, 0, large});
    wide.add_line(large, large, 17);
    auto wide_state = wide.snapshot();
    wide.add_line(-large, large, 3);
    assert(wide.query_with_id(large) == make_pair(-large * large + large, 3));
    assert(wide.query_with_id(0) == make_pair(large, 3));
    wide.rollback(wide_state);
    assert(wide.query_with_id(large) == make_pair(large * large + large, 17));
}
