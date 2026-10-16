#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;

#include "../string/count_words.cpp"
#include "../string/avoid_patterns.cpp"
#include "../math/digit_dfa.cpp"
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
    for (int tc = 0; tc < 500; ++tc) {
        int s = 1 + rng() % 12;
        DFA<3> a{vector<array<int, 3>>(s), vector<char>(s), int(rng() % (s + 1)) - 1};
        for (int v = 0; v < s; ++v) {
            a.accept[v] = rng() % 2;
            for (int& to : a.next[v]) to = int(rng() % (s + 1)) - 1;
        }
        auto expected = direct(a, 97);
        for (int n : {0, 1, 2 * s - 1, 2 * s, 2 * s + 1, 97}) {
            assert(count_words(a, n) == expected[n]);
        }
        ll n = tc % 7 == 0 ? largest : 1000000000000000000LL - rng();
        assert(count_words(a, n) == dense(a, n));
    }
    assert(count_words(DFA<2>{}, 0) == mint(0));
    assert(count_words(DFA<2>{}, largest) == mint(0));
    DFA<2> empty_only{vector<array<int, 2>>(1), {true}, 0};
    empty_only.next[0].fill(-1);
    assert(count_words(empty_only, 0) == mint(1));
    assert(count_words(empty_only, 1) == mint(0));
    assert(count_words(empty_only, largest) == mint(0));
    DFA<2> chain{vector<array<int, 2>>(64), vector<char>(64), 0};
    chain.accept.back() = true;
    for (int v = 0; v < 64; ++v) chain.next[v].fill(v == 63 ? -1 : v + 1);
    for (ll n : {0LL, 62LL, 63LL, 64LL, 127LL, 128LL, largest}) {
        assert(count_words(chain, n) == (n == 63 ? mint(2).pow(63) : mint(0)));
    }
    for (ll n : {0LL, 1LL, 2LL, 97LL, largest}) {
        assert(count_words(required_digits(0), n) == mint(10).pow(n));
    }
    auto reject = required_digits(0);
    reject.accept[0] = false;
    assert(count_words(reject, largest) == mint(0));
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

int main() {
    self_check();
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
