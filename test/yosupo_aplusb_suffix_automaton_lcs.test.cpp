#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../string/suffix_automaton.cpp"

template<int W>
void check(const string &s, const string &t, const SuffixAutomaton<W> &sam) {
    int n = s.size(), m = t.size(), best = 0;
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
        if (s[i] == t[j]) dp[i + 1][j + 1] = dp[i][j] + 1;
        best = max(best, dp[i + 1][j + 1]);
    }
    auto match = sam.longest_common_substring(t);
    assert(0 <= match.s_l && match.s_l <= match.s_r && match.s_r <= n);
    assert(0 <= match.t_l && match.t_l <= match.t_r && match.t_r <= m);
    assert(match.s_r - match.s_l == best && match.t_r - match.t_l == best);
    assert(s.substr(match.s_l, best) == t.substr(match.t_l, best));
    if (!best) assert(match.s_l == 0 && match.s_r == 0 && match.t_l == 0 && match.t_r == 0);
    auto repeat = sam.longest_common_substring(vector<char>(t.begin(), t.end()));
    assert(tie(match.s_l, match.s_r, match.t_l, match.t_r) == tie(repeat.s_l, repeat.s_r, repeat.t_l, repeat.t_r));
}

template<int W>
void exhaustive(int max_length) {
    vector<string> words;
    for (int n = 0, count = 1; n <= max_length; ++n, count *= W) {
        for (int mask = 0; mask < count; ++mask) {
            string s(n, 'a');
            int x = mask;
            for (char &c : s) c += x % W, x /= W;
            words.push_back(s);
        }
    }
    for (string s : words) {
        SuffixAutomaton<W> sam(s);
        for (const auto &t : words) check(s, t, sam);
        for (char c : {'b', 'a', 'b'}) {
            s += c;
            sam.add(c);
            for (const auto &t : words) check(s, t, sam);
        }
    }
}

int main() {
    exhaustive<2>(6);
    exhaustive<3>(4);
    mt19937 rng(129);
    for (int tc = 0; tc < 500; ++tc) {
        string s;
        SuffixAutomaton<3> sam;
        for (int step = 0; step < 10; ++step) {
            string t(rng() % 40, 'a');
            for (char &c : t) c = "abc$\0\xff"[rng() % 6];
            check(s, t, sam);
            char c = 'a' + rng() % 3;
            s += c;
            sam.add(c);
            check(s, t, sam);
        }
    }
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
