#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../util/lis.cpp"

template<class T>
void check(const vector<T> &a) {
    int n = a.size();
    for (bool strict : {false, true}) {
        int best = 0;
        for (int mask = 0; mask < (1 << n); ++mask) {
            int previous = -1, length = 0;
            bool ok = true;
            for (int i = 0; i < n; ++i) if (mask >> i & 1) {
                if (previous >= 0)
                    ok &= strict ? a[previous] < a[i] : !(a[i] < a[previous]);
                previous = i;
                ++length;
            }
            if (ok) best = max(best, length);
        }
        auto indices = lis_indices(a, strict);
        assert((int)indices.size() == best);
        assert(lis_length(a, strict) == best);
        for (int i = 0; i < best; ++i) {
            assert(0 <= indices[i] && indices[i] < n);
            if (!i) continue;
            assert(indices[i - 1] < indices[i]);
            assert(strict ? a[indices[i - 1]] < a[indices[i]] : !(a[indices[i]] < a[indices[i - 1]]));
        }
    }
}

struct Value {
    int x;
    explicit Value(int x): x(x) {}
    bool operator<(const Value &other) const { return x < other.x; }
};

template<class T>
void check_dp(const vector<T>& a) {
    for (bool strict : {false, true}) {
        vector<int> dp(a.size(), 1);
        int best = 0;
        for (int i = 0; i < (int)a.size(); ++i) {
            for (int j = 0; j < i; ++j) {
                if (strict ? a[j] < a[i] : !(a[i] < a[j])) dp[i] = max(dp[i], dp[j] + 1);
            }
            best = max(best, dp[i]);
        }
        assert(lis_length(a, strict) == best);
        assert((int)lis_indices(a, strict).size() == best);
    }
}

int main() {
    for (int n = 0, count = 1; n <= 8; ++n, count *= 3) {
        for (int mask = 0; mask < count; ++mask) {
            vector<int> a(n);
            int x = mask;
            for (auto &v : a) v = x % 3 - 1, x /= 3;
            check(a);
        }
    }
    check(vector<long long>{LLONG_MIN, LLONG_MAX, LLONG_MIN, 0, LLONG_MAX, LLONG_MAX});
    check(vector<string>{"b", "a", "a", "c", "b", "d"});
    check(vector<Value>{Value(2), Value(1), Value(1), Value(3)});
    assert(lis_length(vector<int>{3, 1, 1, 2}) == 2);
    check_dp(vector<string>{string(4096, 'b'), string(4096, 'a'), string(4096, 'a'), string(4096, 'c')});
    mt19937 rng(275);
    for (int tc = 0; tc < 5000; ++tc) {
        vector<int> a(rng() % 100);
        for (int& x : a) x = (int)(rng() % 21) - 10;
        check_dp(a);
    }
    vector<int> ordered(200);
    iota(ordered.begin(), ordered.end(), -100);
    check_dp(ordered);
    reverse(ordered.begin(), ordered.end());
    check_dp(ordered);
    check_dp(vector<int>(200, -1));
}
