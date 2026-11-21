#define STANDALONE

#include <bits/stdc++.h>
using namespace std;

#include "../datastructure/heap/double_ended_priority_queue.cpp"

void check(const DoubleEndedPriorityQueue<int> &heap, const multiset<int> &expected) {
    assert(heap.size() == expected.size());
    assert(heap.empty() == expected.empty());
    if (!expected.empty()) {
        assert(heap.min() == *expected.begin());
        assert(heap.max() == *expected.rbegin());
    }
}

void pop(DoubleEndedPriorityQueue<int> &heap, multiset<int> &expected, bool upper) {
    auto it = upper ? prev(expected.end()) : expected.begin();
    int value = upper ? heap.pop_max() : heap.pop_min();
    assert(value == *it);
    expected.erase(it);
}

struct Key {
    int value;
    static inline int comparisons = 0;
    bool operator<(const Key &other) const {
        ++comparisons;
        return value < other.value;
    }
};

int main() {
    mt19937 rng(563);
    for (int n = 0; n <= 130; ++n) {
        vector<int> values(n);
        for (int &v : values) v = int(rng() % 21) - 10;
        for (int mode = 0; mode < 3; ++mode) {
            DoubleEndedPriorityQueue<int> heap(values);
            multiset<int> expected(values.begin(), values.end());
            while (!expected.empty()) {
                check(heap, expected);
                pop(heap, expected, mode == 1 || (mode == 2 && expected.size() % 2));
            }
            check(heap, expected);
        }
    }

    DoubleEndedPriorityQueue<int> heap;
    heap.reserve(10000);
    multiset<int> expected;
    for (int i = 0; i < 100000; ++i) {
        if (expected.empty() || rng() % 2) {
            int value = int(rng() % 101) - 50;
            heap.push(value);
            expected.insert(value);
        } else {
            pop(heap, expected, rng() % 2);
        }
        check(heap, expected);
    }

    vector<Key> values(16384);
    for (int i = 0; i < (int)values.size(); ++i) values[i].value = i;
    DoubleEndedPriorityQueue<Key> ordered(std::move(values));
    assert(Key::comparisons < 6 * (int)ordered.size());
    assert(ordered.min().value == 0 && ordered.max().value == 16383);
}
