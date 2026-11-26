#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../datastructure/slidingwindow.cpp"

template<class T>
void check() {
    mt19937 rng(59);
    vector<T> values(400);
    for (int i = 0; i < int(values.size()); ++i) values[i] = T(rng() % 17);
    const auto initial = values;
    for (bool maximum : {false, true}) {
        values = initial;
        auto cmp = [=](T a, T b) { return maximum ? a > b : a < b; };
        sliding_window<T, decltype(cmp)> sw(values, cmp);
        static_assert(is_same_v<decltype(sw.get_index()), int>);
        static_assert(is_same_v<decltype(sw.value()), T>);
        auto verify = [&](int width) {
            assert(sw.l == 0 && sw.r == 0);
            assert(sw.get_index() == 0 && sw.value() == T(0));
            for (int r = 1; r <= int(values.size()); ++r) {
                sw.slideR();
                if (sw.r - sw.l > width) sw.slideL();
                int best = sw.l;
                for (int i = sw.l + 1; i < sw.r; ++i)
                    if (!cmp(values[best], values[i])) best = i;
                assert(sw.get_index() == best);
                assert(sw.value() == values[best]);
            }
            while (sw.l < sw.r) sw.slideL();
            assert(sw.get_index() == 0 && sw.value() == T(0));
        };
        for (int width : {1, 7, 65}) {
            sw.reset();
            verify(width);
        }
        reverse(values.begin(), values.end());
        sw.set(values);
        verify(23);
        values.assign(33001, T(1));
        values.back() = T(0);
        sw.set(values);
        verify(1);
        values.resize(400);
    }
}

void check_streaming_dp() {
    mt19937 rng(529);
    vector<int> cost(200);
    for (int& x : cost) x = int(rng() % 19) - 9;
    for (int width : {1, 2, 17, 200}) {
        monotonic_queue<long long> q;
        q.push(0LL);
        vector<long long> dp{0};
        for (int i = 1; i <= int(cost.size()); ++i) {
            int left = max(0, i - width);
            q.pop_until(left);
            int best = left;
            for (int j = left + 1; j < i; ++j)
                if (dp[j] <= dp[best]) best = j;
            assert(q.front() == make_pair(best, dp[best]));
            long long next = q.front().second + cost[i - 1];
            q.push(next);
            dp.push_back(dp[best] + cost[i - 1]);
        }
        assert(q.front().second == *min_element(dp.end() - width - 1, dp.end()));
    }
}

void check_sparse_fifo() {
    using P = pair<long long, int>;
    monotonic_queue<P> q;
    assert(q.empty());
    q.push(2, {8, 1});
    q.push(7, {4, 2});
    q.push(19, {4, 2});
    q.push(40, {6, 0});
    q.pop();
    assert(q.front() == make_pair(19, P{4, 2}));
    q.pop_until(19);
    assert(q.front() == make_pair(19, P{4, 2}));
    q.pop();
    assert(q.front() == make_pair(40, P{6, 0}));
    q.pop_until(100);
    assert(q.empty());
    q.push({3, 5});
    assert(q.front() == make_pair(41, P{3, 5}));
}

template<class F>
void check_stream(F compare) {
    using P = pair<long long, int>;
    monotonic_queue<P, F> q(compare);
    deque<pair<int, P>> live;
    mt19937 rng(530);
    int last = -1;
    for (int step = 0; step < 10000; ++step) {
        int operation = rng() % 5;
        if (operation < 3 || live.empty()) {
            P value{rng() % 5, rng() % 3};
            if (operation == 0) {
                ++last;
                q.push(value);
            } else {
                last += 1 + int(rng() % 20);
                q.push(last, value);
            }
            live.emplace_back(last, value);
        } else if (operation == 3) {
            q.pop();
            live.pop_front();
        } else {
            int cutoff = live.front().first + int(rng() % 70) - 5;
            q.pop_until(cutoff);
            while (!live.empty() && live.front().first < cutoff) live.pop_front();
        }
        assert(q.empty() == live.empty());
        if (!live.empty()) {
            auto best = live.front();
            for (const auto& x : live)
                if (!compare(best.second, x.second)) best = x;
            assert(q.front() == best);
        }
    }
}

struct Score {
    int key;
    explicit Score(int key) : key(key) {}
    bool operator<(const Score& other) const { return key < other.key; }
};

void check_score() {
    const vector<Score> scores{Score(8), Score(3), Score(3)};
    auto original = scores;
    sliding_window<Score, less<Score>> sw(original, {});
    original[0] = Score(1);
    sw.slideR();
    assert(sw.value().key == 8);
    sw.set(scores);
    for (int i = 0; i < 3; ++i) sw.slideR();
    assert(sw.get_index() == 2 && sw.value().key == 3);
    monotonic_queue<Score> q;
    q.push(Score(8));
    q.push(Score(3));
    q.push(Score(3));
    assert(q.front().first == 2 && q.front().second.key == 3);
}

int main() {
    check<unsigned char>();
    check<signed char>();
    check<short>();
    check<bool>();
    check<int>();
    check<long long>();
    check_streaming_dp();
    check_sparse_fifo();
    check_stream(less<>{});
    check_stream(greater<>{});
    check_stream(less_equal<>{});
    check_score();
}
