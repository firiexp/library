#define STANDALONE
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;

#include "../string/count_words.cpp"
#include "../string/avoid_patterns.cpp"
#include "../math/digit_dfa.cpp"
#include "../string/dfa_minimize.cpp"
#include "../util/fastio.cpp"

template<int W>
vector<mint> direct(const DFA<W>& a, int length) {
    vector<mint> result(length + 1), dp(a.next.size());
    if (a.initial == -1) return result;
    dp[a.initial] = 1;
    for (int n = 0; n <= length; ++n) {
        vector<mint> next(dp.size());
        for (int v = 0; v < (int)dp.size(); ++v) {
            if (a.accept[v]) result[n] += dp[v];
            for (int to : a.next[v]) if (to != -1) next[to] += dp[v];
        }
        dp.swap(next);
    }
    return result;
}

template<int W>
mint dense(const DFA<W>& a, ll n) {
    if (a.initial == -1) return 0;
    int s = a.next.size();
    vector<vector<mint>> mat(s, vector<mint>(s));
    for (int v = 0; v < s; ++v) for (int to : a.next[v]) if (to != -1) mat[v][to] += 1;
    vector<mint> dp(s);
    dp[a.initial] = 1;
    while (n) {
        if (n & 1) {
            vector<mint> next(s);
            for (int v = 0; v < s; ++v) {
                for (int to = 0; to < s; ++to) next[to] += dp[v] * mat[v][to];
            }
            dp.swap(next);
        }
        n >>= 1;
        if (!n) break;
        vector<vector<mint>> next(s, vector<mint>(s));
        for (int i = 0; i < s; ++i) {
            for (int k = 0; k < s; ++k) {
                for (int j = 0; j < s; ++j) next[i][j] += mat[i][k] * mat[k][j];
            }
        }
        mat.swap(next);
    }
    mint result = 0;
    for (int v = 0; v < s; ++v) if (a.accept[v]) result += dp[v];
    return result;
}

void self_check() {
    mt19937 rng(151);
    const ll largest = numeric_limits<ll>::max();
    DFA<2> only_a{{{0, -1}}, {true}, 0};
    DFA<2> only_b{{{-1, 0}}, {true}, 0};
    auto either = unite(only_a, only_b);
    auto neither = complement(either);
    const DFAWordCounter<2> either_counter(either), neither_counter(neither);
    for (ll n : {0LL, 1LL, 2LL, 8LL, 97LL, 1000000000000000000LL, largest}) {
        mint expected = n == 0 ? mint(1) : mint(2);
        assert(count_words(either, n) == expected);
        assert(count_words(neither, n) == mint(2).pow(n) - expected);
        assert(either_counter.count(n) == expected);
        assert(neither_counter.count(n) == mint(2).pow(n) - expected);
        assert(count_words(minimize(either), n) == expected);
        assert(count_words(minimize(neither), n) == mint(2).pow(n) - expected);
    }
    for (int tc = 0; tc < 500; ++tc) {
        int s = 1 + rng() % 12;
        DFA<3> a{vector<array<int, 3>>(s), vector<char>(s), int(rng() % (s + 1)) - 1};
        for (int v = 0; v < s; ++v) {
            a.accept[v] = rng() % 2;
            for (int& to : a.next[v]) to = int(rng() % (s + 1)) - 1;
        }
        auto expected = direct(a, 97);
        const DFAWordCounter<3> counter(a);
        vector<int> lengths{0, 1, 2 * s - 1, 2 * s, 2 * s + 1, 97};
        shuffle(lengths.begin(), lengths.end(), rng);
        for (int n : lengths) {
            assert(count_words(a, n) == expected[n]);
            assert(counter.count(n) == expected[n]);
        }
        ll n = tc % 7 == 0 ? largest : 1000000000000000000LL - rng();
        mint large_expected = dense(a, n);
        assert(count_words(a, n) == large_expected);
        assert(counter.count(n) == large_expected);
        a = DFA<3>{};
        assert(counter.count(n) == large_expected);
        for (int length : lengths) assert(counter.count(length) == expected[length]);
    }
    assert(count_words(DFA<2>{}, 0) == mint(0));
    assert(count_words(DFA<2>{}, largest) == mint(0));
    const DFAWordCounter<2> empty_counter(DFA<2>{});
    assert(empty_counter.count(0) == mint(0));
    assert(empty_counter.count(largest) == mint(0));
    DFA<2> empty_only{vector<array<int, 2>>(1), {true}, 0};
    empty_only.next[0].fill(-1);
    assert(count_words(empty_only, 0) == mint(1));
    assert(count_words(empty_only, 1) == mint(0));
    assert(count_words(empty_only, largest) == mint(0));
    const DFAWordCounter<2> empty_only_counter(empty_only);
    assert(empty_only_counter.count(0) == mint(1));
    assert(empty_only_counter.count(1) == mint(0));
    assert(empty_only_counter.count(largest) == mint(0));
    DFA<2> chain{vector<array<int, 2>>(64), vector<char>(64), 0};
    chain.accept.back() = true;
    for (int v = 0; v < 64; ++v) chain.next[v].fill(v == 63 ? -1 : v + 1);
    const DFAWordCounter<2> chain_counter(chain);
    for (ll n : {0LL, 62LL, 63LL, 64LL, 127LL, 128LL, largest}) {
        assert(count_words(chain, n) == (n == 63 ? mint(2).pow(63) : mint(0)));
        assert(chain_counter.count(n) == (n == 63 ? mint(2).pow(63) : mint(0)));
    }
    const DFAWordCounter<10> all_counter(required_digits(0));
    for (ll n : {0LL, 1LL, 2LL, 97LL, largest}) {
        assert(count_words(required_digits(0), n) == mint(10).pow(n));
        assert(all_counter.count(n) == mint(10).pow(n));
    }
    auto reject = required_digits(0);
    reject.accept[0] = false;
    assert(count_words(reject, largest) == mint(0));
    const DFAWordCounter<10> reject_counter(reject);
    assert(reject_counter.count(0) == mint(0));
    assert(reject_counter.count(largest) == mint(0));
    DFA<2> unreachable{{{0, 0}, {1, 1}}, {false, true}, 0};
    const DFAWordCounter<2> zero_counter(unreachable);
    for (ll n : {0LL, 1LL, 3LL, 4LL, largest}) assert(zero_counter.count(n) == mint(0));
    for (int tc = 0; tc < 100; ++tc) {
        int s = 20 + rng() % 80;
        DFA<32> a{vector<array<int, 32>>(s), vector<char>(s), int(rng() % s)};
        for (int v = 0; v < s; ++v) {
            a.accept[v] = rng() % 2;
            for (int& to : a.next[v]) to = rng() % 5 == 0 ? -1 : int(rng() % s);
        }
        auto expected = direct(a, 2 * s + 10);
        const DFAWordCounter<32> counter(a);
        for (int n : {1, 2, s, 2 * s + 10}) {
            assert(count_words(a, n) == expected[n]);
            assert(counter.count(n) == expected[n]);
        }
    }
    DFA<2> wide{vector<array<int, 2>>(511), vector<char>(511, true), 0};
    for (int v = 0; v < 511; ++v) {
        wide.next[v] = {v < 255 ? 2 * v + 1 : 0, v < 255 ? 2 * v + 2 : 0};
    }
    const DFAWordCounter<2> wide_counter(wide);
    for (int n : {7, 8, 9, 15, 16, 17, 1022, 1023}) {
        assert(count_words(wide, n) == mint(2).pow(n));
        assert(wide_counter.count(n) == mint(2).pow(n));
    }
    auto compact = minimize(digit_value_mod(100));
    for (ll n : {1LL, 2LL, 3LL, 100LL, largest}) {
        mint expected = n < 2 ? mint(1) : mint(10).pow(n - 2);
        assert(count_words(compact, n) == expected);
    }
    auto combined = intersect(no_equal_adjacent(), digit_value_mod(7));
    auto expected = direct(combined, 200);
    for (int n : {0, 1, 2, 19, 200}) assert(count_words(combined, n) == expected[n]);
    for (int tc = 0; tc < 100; ++tc) {
        vector<string> patterns;
        int k = rng() % 5;
        while (k--) {
            string pattern(rng() % 6, 'a');
            for (char& c : pattern) c += rng() % 2;
            patterns.push_back(pattern);
        }
        auto a = avoid_patterns<2, 'a'>(patterns);
        for (int n = 0; n <= 10; ++n) {
            int expected = 0;
            for (int mask = 0; mask < (1 << n); ++mask) {
                string s(n, 'a');
                for (int i = 0; i < n; ++i) s[i] += mask >> i & 1;
                bool ok = true;
                for (const auto& pattern : patterns) ok &= s.find(pattern) == string::npos;
                expected += ok;
            }
            assert(count_words(a, n) == mint(expected));
        }
    }
}

template<int W>
void check_compression() {
    mt19937 rng(278 + W);
    for (int trial = 0; trial < 90; ++trial) {
        int s = 32 + rng() % 65;
        DFA<W> a{vector<array<int, W>>(s), vector<char>(s), 0};
        for (int v = 0; v < s; ++v) {
            a.accept[v] = rng() % 2;
            int target = rng() % s;
            for (int c = 0; c < W; ++c) {
                if (trial % 3 == 0) a.next[v][c] = c == 0 ? (v + 1) % s : target;
                if (trial % 3 == 1) a.next[v][c] = c < 2 ? -1 : (v + 1) % s;
                if (trial % 3 == 2) a.next[v][c] = (v + c + 1) % s;
            }
        }
        if (trial % 17 == 0) a.accept.assign(s, false);
        if (trial % 19 == 0) a.next[s / 2].fill(-1);
        auto expected = direct(a, 2 * s + 17);
        const DFAWordCounter<W> counter(a);
        for (int n : {0, 1, 17, 31, 32, 33, 55, 2 * s - 1, 2 * s, 2 * s + 17}) {
            assert(count_words(a, n) == expected[n]);
            assert(counter.count(n) == expected[n]);
        }
    }
    int s = 128;
    DFA<W> all{vector<array<int, W>>(s), vector<char>(s, true), 0};
    for (int v = 0; v < s; ++v) {
        all.next[v].fill(0);
        all.next[v][0] = (v + 1) % s;
    }
    const DFAWordCounter<W> counter(all);
    for (ll n : {0LL, 33LL, 128LL, 511LL, LLONG_MAX}) {
        assert(count_words(all, n) == mint(W).pow(n));
        assert(counter.count(n) == mint(W).pow(n));
    }
    for (auto &row : all.next) row.fill(-1);
    assert(count_words(all, 33) == mint(0));
    DFA<W> shrinking{vector<array<int, W>>(W + 40), vector<char>(W + 40), 0};
    for (auto &row : shrinking.next) row.fill(W + 1);
    for (int c = 0; c < W; ++c) shrinking.next[0][c] = c + 1;
    shrinking.accept[W + 1] = true;
    const DFAWordCounter<W> shrinking_counter(shrinking);
    for (int n : {0, 1, 2, 33, 200}) {
        mint expected = n < 2 ? mint(0) : mint(W).pow(n);
        assert(count_words(shrinking, n) == expected);
        assert(shrinking_counter.count(n) == expected);
    }
    DFA<W> mixed{vector<array<int, W>>(64), vector<char>(64), 1};
    for (int v = 0; v < 64; ++v) {
        mixed.accept[v] = v % 3 == 0;
        for (int c = 0; c < W; ++c) mixed.next[v][c] = v % 4 == 0 ? 0 : (v + c + 1) % 64;
    }
    auto expected = direct(mixed, 200);
    const DFAWordCounter<W> mixed_counter(mixed);
    for (int n : {33, 127, 128, 200}) {
        assert(count_words(mixed, n) == expected[n]);
        assert(mixed_counter.count(n) == expected[n]);
    }
}

int main() {
    self_check();
    check_compression<6>();
    check_compression<26>();
    check_compression<64>();
}
