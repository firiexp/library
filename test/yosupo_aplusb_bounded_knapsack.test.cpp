#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template<class T> constexpr T INF = numeric_limits<T>::max() / 32 * 15 + 208;
#include "../util/fastio.cpp"
#include "../math/bounded_knapsack.cpp"

void check(const vector<BoundedKnapsackItem>& items, int capacity) {
    vector<long long> expected(capacity + 1, -INF<ll>);
    expected[0] = 0;
    for (auto item : items) {
        auto next = expected;
        for (int w = 0; w <= capacity; ++w) {
            if (expected[w] == -INF<ll>) continue;
            int limit = (int)min(item.count, (long long)(capacity - w) / item.weight);
            for (int k = 1; k <= limit; ++k)
                next[w + k * item.weight] = max(next[w + k * item.weight], expected[w] + k * item.value);
        }
        expected = std::move(next);
    }
    auto original = items;
    assert(bounded_knapsack(items, capacity) == expected);
    for (int i = 0; i < (int)items.size(); ++i) {
        assert(items[i].weight == original[i].weight);
        assert(items[i].value == original[i].value);
        assert(items[i].count == original[i].count);
    }
}

void self_check() {
    check({}, 0);
    check({}, 20);
    check({{1, 5, 0}, {INT_MAX, 1, LLONG_MAX}}, 30);
    check({{3, -4, LLONG_MAX}, {5, 2, 0}}, 0);
    check({{1, LLONG_MAX, 1}}, 1);
    check({{1, -INF<ll> + 1, 1}}, 2);
    check({{2, -INF<ll> + 1, 1}}, 3);
    check({{1, -INF<ll> + 1, 1}, {1, INF<ll> - 2, 1}}, 2);
    check({{1, (-INF<ll> + 1) / 33, 33}}, 34);
    check({{3, 4, 2}, {1, 2, 1}, {2, 1, 4}, {2, 3, 2}}, 8);
    check({{1, 1, 100}, {1, 2, 50}}, 100);
    check({{7, -3, 40}, {1, 2, 41}, {13, 0, 35}, {3, -4, 50}, {2, 7, 3}, {9, 1, LLONG_MAX}}, 600);
    check({{1, 7, 40}, {13, -2, 40}, {7, 0, 40}, {1, -1, 33}}, 600);
    vector<BoundedKnapsackItem> skipped(200000, {65, 1, 10});
    skipped[100000] = {1, -2, 40};
    check(skipped, 64);
    for (int count : {0, 1, 2, 31, 32, 33, 64, 99, 100, 101}) {
        for (int value : {-7, 0, 11}) {
            check({{3, value, count}}, 302);
            check({{1, -3, LLONG_MAX}, {3, value, count}, {3, 5, count}}, 302);
        }
    }
    mt19937 rng(160);
    for (int tc = 0; tc < 4000; ++tc) {
        int n = rng() % 9, capacity = rng() % 160;
        vector<BoundedKnapsackItem> items;
        for (int i = 0; i < n; ++i) {
            int weight = 1 + rng() % 12;
            long long value = (int)(rng() % 41) - 20;
            long long count = rng() % 90;
            if (rng() % 10 == 0) count = LLONG_MAX;
            items.push_back({weight, value, count});
        }
        check(items, capacity);
    }
}

int main() {
    self_check();
}
