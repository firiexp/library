#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../string/kmp.cpp"

vector<long long> naive(const string &text, const string &pattern) {
    vector<long long> result;
    for (size_t i = 0; i + pattern.size() <= text.size(); ++i) {
        if (text.compare(i, pattern.size(), pattern) == 0) result.push_back(i);
    }
    return result;
}

void check(const string &text, const string &pattern, mt19937 &rng) {
    auto expected = naive(text, pattern);
    auto single = kmp_search(text, pattern);
    assert(vector<long long>(single.begin(), single.end()) == expected);
    KMPMatcher matcher(pattern);
    for (int repeat = 0; repeat < 3; ++repeat) {
        vector<long long> result;
        auto emit = [&](long long pos) { result.push_back(pos); };
        matcher.scan("", emit);
        matcher.scan("", emit);
        size_t offset = 0;
        while (offset < text.size()) {
            size_t length = min(text.size() - offset, size_t(rng() % 9 + 1));
            matcher.scan(string_view(text).substr(offset, length), emit);
            matcher.scan("", emit);
            offset += length;
        }
        matcher.scan("", emit);
        assert(result == expected);
        matcher.reset();
    }
    string other = pattern + text + pattern;
    vector<long long> result;
    matcher.scan(other, [&](long long pos) { result.push_back(pos); });
    assert(result == naive(other, pattern));
}

int main() {
    mt19937 rng(230);
    vector<string> fixed = {"", "a", "aaaaaaa", "aba", "ababa", "abababab", "ababcababa"};
    fixed.emplace_back("\0\x80\xff\0\x80\xff", 6);
    fixed.emplace_back("\x80\xff\0", 3);
    for (const auto &text : fixed) for (const auto &pattern : fixed) check(text, pattern, rng);
    for (int tc = 0; tc < 10000; ++tc) {
        string text(rng() % 80, 'a'), pattern(rng() % 15, 'a');
        const string alphabet("ab\0\x80\xff", 5);
        for (char &c : text) c = alphabet[rng() % alphabet.size()];
        for (char &c : pattern) c = alphabet[rng() % alphabet.size()];
        check(text, pattern, rng);
    }
    KMPMatcher owned(string("aba"));
    long long matches = 0;
    owned.scan("ab", [&](long long) { ++matches; });
    auto copy = owned;
    owned.scan("a", [&](long long pos) { assert(pos == 0); ++matches; });
    copy.scan("aba", [&](long long) { ++matches; });
    assert(matches == 3);
}
