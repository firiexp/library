#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../string/ahocorasick_matcher.cpp"
#include "../string/ahocorasick_matcher.cpp"

using Match = pair<int, size_t>;

vector<Match> oracle(const vector<string> &patterns, const string &text) {
    vector<Match> result;
    for (int id = 0; id < (int)patterns.size(); ++id) {
        for (size_t i = 0; i + patterns[id].size() <= text.size(); ++i) {
            if (text.compare(i, patterns[id].size(), patterns[id]) == 0) result.emplace_back(id, i);
        }
    }
    sort(result.begin(), result.end(), [&](Match a, Match b) {
        size_t end_a = a.second + patterns[a.first].size();
        size_t end_b = b.second + patterns[b.first].size();
        if (end_a != end_b) return end_a < end_b;
        if (a.second != b.second) return a.second < b.second;
        return a.first < b.first;
    });
    return result;
}

void check(const vector<string> &patterns, const vector<string> &texts) {
    const AhoCorasickMatcher<3, 'a'> matcher(patterns);
    for (const string &text : texts) {
        vector<Match> got;
        matcher.scan(text, [&](int id, size_t position) { got.emplace_back(id, position); });
        assert(got == oracle(patterns, text));
    }
}

int main() {
    check({}, {"", "abc", "aaaa"});
    check({"", ""}, {"", "abc"});
    check({"aba", "ba", "aba", "a", "", "aa", "aaa"}, {"", "ababa", "aaaaaaa", "cc", "ababa"});
    check({"aab", "ab", "b", "ba", "bc", "bca", "c", "caa"}, {"abccab", "caabaabc", "bbca"});
    mt19937 rng(312);
    auto random_string = [&](int limit) {
        string s(rng() % (limit + 1), 'a');
        for (char &c : s) c += rng() % 3;
        return s;
    };
    for (int trial = 0; trial < 1000; ++trial) {
        vector<string> patterns(rng() % 20), texts(5);
        for (string &s : patterns) s = random_string(10);
        for (string &s : texts) s = random_string(40);
        check(patterns, texts);
    }
    const AhoCorasickMatcher<2, 'a'> deep({string(200000, 'a') + 'b', ""});
    size_t count = 0;
    deep.scan(string(300000, 'a'), [&](int id, size_t position) {
        assert(id == 1 && position == count);
        ++count;
    });
    assert(count == 300001);
    vector<string> nested;
    for (int i = 0; i <= 128; ++i) nested.emplace_back(i, 'a');
    const AhoCorasickMatcher<1, 'a'> many(nested);
    count = 0;
    many.scan(string(10000, 'a'), [&](int id, size_t position) {
        assert(position + id <= 10000);
        ++count;
    });
    assert(count == 129ULL * 10001 - 128 * 129 / 2);
}
