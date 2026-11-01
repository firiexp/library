#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../math/quotient_ranges.cpp"

void check(long long n, long long first, bool enumerate) {
    long long previous = first - 1, previous_q = 0;
    int calls = 0;
    __int128 sum = 0, weighted = 0;
    for_each_quotient(n, [&](long long l, long long r, long long q) {
        assert(l == previous + 1 && l <= r && r <= n);
        assert(q == n / l && q == n / r);
        assert(l == first || n / (l - 1) > q);
        assert(r == n || n / (r + 1) < q);
        assert(!calls || q < previous_q);
        if (enumerate) for (long long i = l; i <= r; ++i) assert(n / i == q);
        sum += __int128(r - l + 1) * q;
        weighted += (__int128(l) + r) * (r - l + 1) / 2 * q;
        previous = r;
        previous_q = q;
        ++calls;
    }, first);
    if (first > n) assert(calls == 0);
    else assert(previous == n && previous_q == 1);
    if (enumerate) {
        __int128 expected = 0, expected_weighted = 0;
        for (long long i = first; i <= n; ++i) {
            expected += n / i;
            expected_weighted += __int128(i) * (n / i);
        }
        assert(sum == expected && weighted == expected_weighted);
    }
}

int main() {
    for (long long n = 0; n <= 5000; ++n) {
        check(n, 1, true);
        check(n, max(1LL, n / 3), true);
        check(n, n + 1, true);
    }
    for (long long root : {100LL, 1000LL, 100000LL, 1000000LL})
        for (long long delta : {-1LL, 0LL, 1LL}) check(root * root + delta, 1, false);
    for (long long n : {LLONG_MAX, LLONG_MAX - 1, LLONG_MAX - 100}) {
        check(n, n / 7, false);
        check(n, n / 2 + 1, false);
        check(n, n, false);
    }
    vector<array<long long, 3>> ranges;
    for_each_quotient(10, [&](long long l, long long r, long long q) {
        ranges.push_back({l, r, q});
    });
    vector<array<long long, 3>> expected{{1, 1, 10}, {2, 2, 5}, {3, 3, 3}, {4, 5, 2}, {6, 10, 1}};
    assert(ranges == expected);
}
