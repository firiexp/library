#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../string/suffix_automaton.cpp"
#include "../string/longest_common_substring.cpp"
#include "../string/longest_common_substring.cpp"

template<int W = 3, char start = 'a'>
void check(const vector<string>& strings) {
    auto result = longest_common_substring<W, start>(strings);
    if (strings.empty()) {
        assert(!result);
        return;
    }
    assert(result);
    int shortest = min_element(strings.begin(), strings.end(), [](const string& a, const string& b) {
        return a.size() < b.size();
    }) - strings.begin();
    const string& word = *result;
    for (const auto& s : strings) assert(s.find(word) != string::npos);
    int expected = 0;
    const auto& s = strings[shortest];
    for (int left = 0; left < (int)s.size(); ++left) {
        for (int length = 1; left + length <= (int)s.size(); ++length) {
            string candidate = s.substr(left, length);
            bool found = true;
            for (const auto& text : strings) found &= text.find(candidate) != string::npos;
            if (found) expected = max(expected, length);
        }
    }
    assert(word.size() == size_t(expected));
    if (strings.size() == 1) assert(word == s);
    if (strings.size() == 2) {
        SuffixAutomaton<W, start> sam(strings[0]);
        auto pair_match = sam.longest_common_substring(strings[1]);
        assert(pair_match.s_r - pair_match.s_l == expected);
    }
}

int main() {
    check({});
    check({""});
    check({"abc"});
    check({"abc", "", "abc"});
    check({"ab", "bc", "ca"});
    check({"abca", "abcb", "ca"});
    check({"ababab", "bababa", "ababab", "bababa"});
    check({"abbbcbcb", "bcbabbbc", "cabbcbcbab"});
    check<10, '0'>({"01230123", "123012", "1234"});
    check<3, '\0'>({string("\0\1\2\0", 4), string("\1\2\0", 3)});
    auto saved = longest_common_substring<3>({"abc", "bca"});
    assert(saved && saved->size() == 2 && *saved == "bc");
    vector<string> words{""};
    for (int n = 1; n <= 3; ++n) for (int mask = 0; mask < (1 << n); ++mask) {
        string word(n, 'a');
        for (int i = 0; i < n; ++i) word[i] += mask >> i & 1;
        words.push_back(word);
    }
    for (const auto& a : words) for (const auto& b : words) for (const auto& c : words)
        check<2>({a, b, c});
    mt19937 rng(434);
    for (int tc = 0; tc < 10000; ++tc) {
        vector<string> strings(rng() % 7);
        for (auto& s : strings) {
            s.resize(rng() % 16, 'a');
            for (char &c : s) c += rng() % 3;
        }
        check(strings);
        shuffle(strings.begin(), strings.end(), rng);
        check(strings);
    }
    check(vector<string>(1000, "abacabcab"));
    vector<string> long_pair{string(200000, 'a'), string(300000, 'a')};
    auto long_match = longest_common_substring<3>(long_pair);
    assert(long_match == optional<string>(string(200000, 'a')));
    vector<string> many(10000, "bbbbbbbbabcacccccccc");
    many.back() = "abca";
    auto many_match = longest_common_substring<3>(many);
    assert(many_match == optional<string>("abca"));
}
