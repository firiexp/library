#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../datastructure/leftist_heap.cpp"

void self_check() {
    mt19937 rng(133);
    LeftistHeap<long long> heap(32);
    vector<multiset<long long>> expected(32);
    for (int step = 0; step < 50000; ++step) {
        int i = rng() % 32, j = rng() % 32, type = rng() % 6;
        long long x = int(rng() % 2001) - 1000;
        if (type < 2) {
            heap.push(i, x);
            expected[i].insert(x);
        } else if (type == 2 && !expected[i].empty()) {
            heap.pop(i);
            expected[i].erase(expected[i].begin());
        } else if (type == 3) {
            heap.meld(i, j);
            if (i != j) expected[i].merge(expected[j]);
        } else if (type == 4) {
            heap.add_all(i, x);
            multiset<long long> next;
            for (long long value : expected[i]) next.insert(value + x);
            expected[i].swap(next);
        } else {
            heap.meld(i, i);
        }
        for (int k = 0; k < 32; ++k) {
            assert(heap.size(k) == (int)expected[k].size());
            assert(heap.empty(k) == expected[k].empty());
            if (!heap.empty(k)) assert(heap.top(k) == *expected[k].begin());
        }
    }
    auto copy = heap;
    for (int i = 0; i < 32; ++i) {
        for (long long x : expected[i]) {
            assert(copy.top(i) == x);
            copy.pop(i);
        }
        assert(copy.empty(i));
        assert(heap.size(i) == (int)expected[i].size());
    }
    int n = 65536;
    for (int mode = 0; mode < 4; ++mode) {
        LeftistHeap<long long> balanced(n);
        vector<long long> values(n);
        for (int i = 0; i < n; ++i) {
            values[i] = mode == 0 ? i : mode == 1 ? -i : mode == 2 ? 7 : (i & 1 ? i : -i);
            balanced.push(i, values[i]);
            balanced.add_all(i, i % 3 - 1);
            values[i] += i % 3 - 1;
        }
        for (int width = 1; width < n; width *= 2)
            for (int i = 0; i < n; i += 2 * width) balanced.meld(i, i + width);
        sort(values.begin(), values.end());
        for (long long x : values) {
            assert(balanced.top(0) == x);
            balanced.pop(0);
        }
        for (int i = 0; i < n; ++i) assert(balanced.empty(i));
        for (int i = 0; i < 100000; ++i) {
            balanced.add_all(0, 999);
            balanced.push(0, i);
            balanced.add_all(0, -3);
            assert(balanced.top(0) == i - 3);
            balanced.pop(0);
        }
    }
}

int main() {
    self_check();
    Scanner in;
    Printer out;
    int a, b;
    in.read(a, b);
    out.println(a + b);
}
