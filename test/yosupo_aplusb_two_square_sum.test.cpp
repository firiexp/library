#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

#include "../math/prime/two_square_sum.cpp"

void check_count(ll n, size_t expected_size) {
    auto pairs = two_square_sum(n);
    assert(pairs.size() == expected_size);
    sort(pairs.begin(), pairs.end());
    assert(adjacent_find(pairs.begin(), pairs.end()) == pairs.end());
    for (auto [x, y] : pairs) {
        assert(x >= 0 && y >= 0);
        assert((__int128)x * x + (__int128)y * y == n);
    }
}

int main() {
    constexpr int limit = 4096;
    vector<vector<pair<ll, ll>>> expected(limit + 1);
    for (int x = 0; x * x <= limit; ++x) {
        for (int y = 0; x * x + y * y <= limit; ++y) {
            expected[x * x + y * y].emplace_back(x, y);
        }
    }
    for (int n = 0; n <= limit; ++n) {
        auto pairs = two_square_sum(n);
        sort(pairs.begin(), pairs.end());
        assert(pairs == expected[n]);
    }

    check_count(9223372030926249577LL, 2);
    check_count(9223372036854775783LL, 0);
    check_count(1000000009LL * 1000000033LL, 4);
    check_count(7450580596923828125LL, 28);
    check_count(2LL * 2147483647 * 2147483647, 1);
    check_count(3037000493LL * 3037000493LL, 4);
    check_count(LLONG_MAX, 0);
}
