#define STANDALONE
#include <bits/stdc++.h>
using namespace std;

#include "../string/avoid_patterns.cpp"
#include "../datastructure/ahocorasick.cpp"
#include "../math/digit_dfa.cpp"
#include "../util/fastio.cpp"

vector<string> words(int max_length) {
    vector<string> result;
    for (int n = 0; n <= max_length; ++n) {
        for (int mask = 0; mask < (1 << n); ++mask) {
            string s(n, 'a');
            for (int i = 0; i < n; ++i) s[i] += mask >> i & 1;
            result.push_back(s);
        }
    }
    return result;
}

void check(const vector<string>& patterns, const vector<string>& texts) {
    auto before = patterns;
    auto a = avoid_patterns<2, 'a'>(patterns);
    assert(before == patterns);
    for (const auto& s : texts) {
        bool expected = true;
        for (const auto& pattern : patterns) expected &= s.find(pattern) == string::npos;
        int v = a.initial;
        for (char c : s) if (v != -1) v = a.next[v][c - 'a'];
        assert((v != -1 && a.accept[v]) == expected);
    }
    assert(a.accept.size() == a.next.size());
    if (a.initial == -1) {
        assert(a.next.empty());
        return;
    }
    vector<char> seen(a.next.size());
    vector<int> q{a.initial};
    seen[a.initial] = true;
    for (size_t i = 0; i < q.size(); ++i) {
        assert(a.accept[q[i]]);
        for (int to : a.next[q[i]]) {
            assert(-1 <= to && to < (int)a.next.size());
            if (to != -1 && !seen[to]) seen[to] = true, q.push_back(to);
        }
    }
    assert(q.size() == a.next.size());
}

void self_check() {
    auto texts = words(8), patterns = words(3);
    check({}, texts);
    check({""}, texts);
    check({"a", "aab", "aab"}, texts);
    check({"b", "aba"}, texts);
    check({"aab", "bbab", "abab"}, texts);
    assert((avoid_patterns<2, 'a'>({"a", "aab"}).next.size() == 1));
    for (const auto& s : patterns) {
        for (const auto& t : patterns) check({s, t}, texts);
    }
    mt19937 rng(150);
    for (int tc = 0; tc < 500; ++tc) {
        vector<string> dictionary;
        int n = rng() % 9;
        while (n--) dictionary.push_back(texts[rng() % texts.size()]);
        check(dictionary, texts);
    }
    auto digits = intersect(avoid_patterns<10, '0'>({"4", "9"}), digit_value_mod(7));
    for (int x = 0; x < 10000; ++x) {
        string s = to_string(x);
        int v = digits.initial;
        for (char c : s) if (v != -1) v = digits.next[v][c - '0'];
        bool expected = x % 7 == 0 && s.find_first_of("49") == string::npos;
        assert((v != -1 && digits.accept[v]) == expected);
    }
}

int main() {
    self_check();
}
