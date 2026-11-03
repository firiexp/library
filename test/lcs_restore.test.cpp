#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../string/lcs_restore.cpp"

void check(const string &a, const string &b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
        dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]);
        if (a[i] == b[j]) dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j] + 1);
    }
    auto result = lcs_restore(a, b);
    assert((int)result.size() == dp[n][m]);
    int prev_i = -1, prev_j = -1;
    for (auto [i, j] : result) {
        assert(prev_i < i && i < n && prev_j < j && j < m);
        assert(a[i] == b[j]);
        prev_i = i;
        prev_j = j;
    }
}

int main() {
    vector<string> strings;
    for (int n = 0; n <= 6; ++n) for (int mask = 0; mask < (1 << n); ++mask) {
        string s(n, 'a');
        for (int i = 0; i < n; ++i) s[i] += (mask >> i) & 1;
        strings.push_back(s);
    }
    for (const auto &a : strings) for (const auto &b : strings) check(a, b);
    check(string(200, 'a'), string(300, 'a'));
    check(string(200, 'a'), string(300, 'b'));
    check("abcbdab", "bdcaba");
    for (auto [a, b] : vector<pair<string, string>>{
        {"abc", "abcabc"}, {"abca", "abcbca"}, {"aabaaa", "aaaaa"},
        {"prefixAsuffix", "prefixBsuffix"}, {"abc", "xabc"}, {"ab", "acb"}}) {
        check(a, b);
        check(b, a);
    }
    check(string("\0\1\xff\0", 4), string("\xff\0\1", 3));
    mt19937 rng(316);
    for (int tc = 0; tc < 700; ++tc) {
        string a(rng() % 70, 'a'), b(rng() % 70, 'a');
        for (char &c : a) c += rng() % 5;
        for (char &c : b) c += rng() % 5;
        check(a, b);
        check(b, a);
    }
    string a(20000, 'a');
    a[123] = 'b';
    a[19999] = 'c';
    check(a, "bacca");
    check("bacca", a);
    assert(lcs_restore(string(100000, 'a'), "").empty());
    assert(lcs_restore("", string(100000, 'a')).empty());
    string same(20000, 'a');
    auto identical = lcs_restore(same, same);
    assert(identical.size() == same.size());
    for (int i = 0; i < (int)same.size(); ++i) assert(identical[i] == make_pair(i, i));
    string longer = same.substr(0, 10000) + "b" + same.substr(10000);
    for (bool swapped : {false, true}) {
        auto result = swapped ? lcs_restore(longer, same) : lcs_restore(same, longer);
        assert(result.size() == same.size());
        for (int i = 0; i < (int)same.size(); ++i) {
            auto expected = make_pair(i, i + (i >= 10000));
            if (swapped) swap(expected.first, expected.second);
            assert(result[i] == expected);
        }
    }
}
