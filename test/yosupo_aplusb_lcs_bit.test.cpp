#define STANDALONE
#include <bits/stdc++.h>

static const int MOD = 1000000007;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
using namespace std;

template<class T> constexpr T INF = ::numeric_limits<T>::max() / 32 * 15 + 208;

#include "../string/lcs_bit.cpp"

#include "../util/fastio.cpp"

void self_check() {
    const string a = "abc", b = "ac";
    assert(LCS_bit(a, b) == 2);
    assert(LCS_bit(b, a) == 2);
    assert(LCS_bit(string("abc"), string("ac")) == 2);
    assert(LCS_bit(a, string()) == 0);
    assert(a == "abc" && b == "ac");
    mt19937 rng(54);
    const vector<int> sizes{0, 1, 63, 64, 65, 127, 128, 129, 191, 192, 193,
        255, 256, 257, 447, 448, 449, 511, 512, 513, 1023, 1024, 1025};
    for (int tc = 0; tc < 2 * (int)sizes.size() * (int)sizes.size(); ++tc) {
        string a(sizes[tc % sizes.size()], '\0');
        string b(sizes[(tc / sizes.size()) % sizes.size()], '\0');
        for (char &c : a) c = char(rng() % (tc % 3 ? 256 : 3));
        for (char &c : b) c = char(rng() % (tc % 3 ? 256 : 3));
        if (tc % 7 == 0) fill(a.begin(), a.end(), '\xff');
        if (tc % 7 <= 1) fill(b.begin(), b.end(), '\xff');
        vector<vector<int>> dp(a.size() + 1, vector<int>(b.size() + 1));
        for (int i = 0; i < (int)a.size(); ++i) for (int j = 0; j < (int)b.size(); ++j)
            dp[i + 1][j + 1] = a[i] == b[j] ? dp[i][j] + 1 : max(dp[i][j + 1], dp[i + 1][j]);
        auto original_a = a, original_b = b;
        assert(LCS_bit(a, b) == dp.back().back());
        assert(LCS_bit(b, a) == dp.back().back());
        assert(a == original_a && b == original_b);
    }
    mt19937_64 words(162);
    for (int size = 1; size <= 33; ++size) {
        for (int tc = 0; tc < 1000; ++tc) {
            vector<ull> dp(size), p(size);
            for (int i = 0; i < size; ++i) {
                dp[i] = tc % 5 == 0 ? 0 : tc % 5 == 1 ? ~0ULL : words();
                p[i] = tc % 3 == 0 ? 0 : tc % 3 == 1 ? ~0ULL : words();
            }
            auto expected = dp;
            ull shift = 1, borrow = 0;
            for (int i = 0; i < size; ++i) {
                ull x = expected[i] | p[i], y = (expected[i] << 1) | shift;
                shift = expected[i] >> 63;
                __uint128_t subtrahend = __uint128_t(y) + borrow;
                borrow = __uint128_t(x) < subtrahend;
                expected[i] = x & ~ull(__uint128_t(x) - subtrahend);
            }
            auto actual = dp;
            lcs_bit_detail::update_scalar(actual.data(), p.data(), size);
            assert(actual == expected);
#if defined(__GNUC__) && defined(__x86_64__)
            if (lcs_bit_detail::backend() >= 1) {
                actual = dp;
                lcs_bit_detail::update_avx2(actual.data(), p.data(), size);
                assert(actual == expected);
            }
            if (lcs_bit_detail::backend() == 2) {
                actual = dp;
                lcs_bit_detail::update_avx512(actual.data(), p.data(), size);
                assert(actual == expected);
            }
#endif
        }
    }
}

int main() {
    self_check();
}
