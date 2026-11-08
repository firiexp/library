#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../string/ahocorasick_matcher.cpp"
#include "../string/ahocorasick_matcher.cpp"

using Match = pair<int, long long>;

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

void check(const vector<string> &patterns, const vector<string> &texts, mt19937 &rng) {
    AhoCorasickMatcher<3, 'a'> matcher(patterns);
    for (const string &text : texts) {
        auto expected = oracle(patterns, text);
        vector<Match> got;
        auto emit = [&](int id, auto position) {
            static_assert(is_same_v<decltype(position), long long>);
            got.emplace_back(id, position);
        };
        matcher.reset();
        matcher.scan(text, emit);
        assert(got == expected);
        for (size_t cut = 0; cut <= text.size(); ++cut) {
            matcher.reset();
            got.clear();
            matcher.scan(string_view(text).substr(0, cut), emit);
            matcher.scan("", emit);
            matcher.scan("", emit);
            matcher.scan(string_view(text).substr(cut), emit);
            matcher.scan("", emit);
            assert(got == expected);
        }
        for (int repeat = 0; repeat < 3; ++repeat) {
            matcher.reset();
            got.clear();
            matcher.scan("", emit);
            for (size_t offset = 0; offset < text.size();) {
                size_t size = min(text.size() - offset, size_t(1 + rng() % 7));
                matcher.scan(string_view(text).substr(offset, size), emit);
                matcher.scan("", emit);
                offset += size;
            }
            assert(got == expected);
        }
    }
}

int main() {
    mt19937 rng(312);
    check({}, {"", "abc", "aaaa"}, rng);
    check({"", ""}, {"", "abc"}, rng);
    check({"aba"}, {"ab", "a", "aba"}, rng);
    check({"aba", "ba", "aba", "a", "", "aa", "aaa"}, {"", "ababa", "aaaaaaa", "cc", "ababa"}, rng);
    check({"aab", "ab", "b", "ba", "bc", "bca", "c", "caa"}, {"abccab", "caabaabc", "bbca"}, rng);
    auto random_string = [&](int limit) {
        string s(rng() % (limit + 1), 'a');
        for (char &c : s) c += rng() % 3;
        return s;
    };
    for (int trial = 0; trial < 1000; ++trial) {
        vector<string> patterns(rng() % 20), texts(5);
        for (string &s : patterns) s = random_string(10);
        for (string &s : texts) s = random_string(40);
        check(patterns, texts, rng);
    }
    AhoCorasickMatcher<2, 'a'> deep({string(200000, 'a') + 'b', ""});
    long long count = 0;
    deep.scan(string(300000, 'a'), [&](int id, long long position) {
        assert(id == 1 && position == count);
        ++count;
    });
    assert(count == 300001);
    vector<string> nested;
    for (int i = 0; i <= 128; ++i) nested.emplace_back(i, 'a');
    AhoCorasickMatcher<1, 'a'> many(nested);
    count = 0;
    many.scan(string(10000, 'a'), [&](int id, long long position) {
        assert(position + id <= 10000);
        ++count;
    });
    assert(count == 129LL * 10001 - 128 * 129 / 2);
}
