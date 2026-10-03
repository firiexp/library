#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../util/xorshift.cpp"

int reference(xor_shift &rng, int a, int b) {
    if (a > b) swap(a, b);
    uint64_t width = int64_t(b) - int64_t(a) + 1;
    uint64_t buckets = (uint64_t(1) << 32) / width;
    for (;;) {
        uint64_t raw = rng.urand(), bucket = raw / width;
        if (bucket < buckets)
            return int(int64_t(a) + int64_t(raw - bucket * width));
    }
}

void self_check() {
    xor_shift rng, raw = rng;
    vector<int> endpoints{INT_MIN, INT_MIN + 1, -2000000000, -1, 0, 1, 7, 2000000000, INT_MAX};
    for (int n : endpoints) for (int i = 0; i < 1000; ++i) {
        int value = rng.rand(n);
        assert(min(0, n) <= value && value <= max(0, n));
        assert(value == reference(raw, 0, n));
    }
    for (int a : endpoints) for (int b : endpoints) for (int i = 0; i < 1000; ++i) {
        int value = rng.rand(a, b);
        assert(min(a, b) <= value && value <= max(a, b));
        assert(value == reference(raw, a, b));
    }
    mt19937 bounds(46);
    for (int i = 0; i < 10000; ++i) {
        int a = int(int64_t(bounds()) + INT_MIN), b = int(int64_t(bounds()) + INT_MIN);
        int value = rng.rand(a, b);
        assert(min(a, b) <= value && value <= max(a, b));
        assert(value == reference(raw, a, b));
    }
    assert(rng.urand() == raw.urand());
}

int main() {
    self_check();
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
