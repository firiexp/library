#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
#include "../util/fastio.cpp"
#include "../math/subset_sum_counts.cpp"

void check(const vector<int>& weights, int t) {
    auto original = weights;
    vector<mint> expected(t + 1);
    expected[0] = 1;
    for (int w : weights) {
        for (int s = t; s >= w; --s) expected[s] += expected[s - w];
    }
    auto result = subset_sum_counts(weights, t);
    assert(result == expected && weights == original);
    if (weights.size() <= 14) {
        vector<mint> enumerated(t + 1);
        for (int mask = 0; mask < (1 << weights.size()); ++mask) {
            ll sum = 0;
            for (int i = 0; i < (int)weights.size(); ++i) if ((mask >> i) & 1) sum += weights[i];
            if (sum <= t) ++enumerated[sum];
        }
        assert(result == enumerated);
    }
}

void self_check() {
    assert(subset_sum_counts({0, 1, 1, 3}, 4) == vector<mint>({2, 4, 2, 2, 4}));
    for (int t : {0, 1, 2, 31, 32, 33, 63, 64, 65, 127, 128, 129, 256}) {
        check({}, t);
        check(vector<int>(100, 0), t);
        check(vector<int>(100, 1), t);
        check(vector<int>(100, 7), t);
        check({0, 0, 1, 1, 3, t + 1, INT_MAX}, t);
    }
    mt19937 rng(78);
    for (int tc = 0; tc < 1200; ++tc) {
        int n = tc < 400 ? rng() % 15 : 15 + rng() % 86;
        int t = rng() % 260;
        vector<int> weights(n);
        for (int& w : weights) w = rng() % (t + 10);
        check(weights, t);
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
