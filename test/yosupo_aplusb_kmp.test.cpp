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

template<class T>
void check_sequence(const vector<T> &text, vector<T> pattern, mt19937 &rng) {
    vector<int> expected;
    for (size_t i = 0; i + pattern.size() <= text.size(); ++i) {
        if (equal(pattern.begin(), pattern.end(), text.begin() + i)) expected.push_back(i);
    }
    assert(kmp_search(text, pattern) == expected);
    KMPMatcher matcher(pattern);
    pattern.clear();
    for (int repeat = 0; repeat < 2; ++repeat) {
        vector<long long> result;
        auto emit = [&](long long p) { result.push_back(p); };
        matcher.scan(vector<T>{}, emit);
        size_t offset = 0;
        while (offset < text.size()) {
            size_t length = min(text.size() - offset, size_t(rng() % 7 + 1));
            if (rng() % 2) matcher.scan(text.begin() + offset, text.begin() + offset + length, emit);
            else matcher.scan(vector<T>(text.begin() + offset, text.begin() + offset + length), emit);
            offset += length;
            matcher.scan(text.end(), text.end(), emit);
        }
        assert(result == vector<long long>(expected.begin(), expected.end()));
        matcher.reset();
    }
}

struct Token {
    int value;
    bool operator==(const Token &other) const { return value == other.value; }
};

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
    assert(kmp_search("ababa", "aba") == vector<int>({0, 2}));
    assert(kmp_search(string("ababa"), "aba") == vector<int>({0, 2}));
    assert(kmp_search("ababa", string("aba")) == vector<int>({0, 2}));
    assert(kmp_table("aba") == vector<int>({-1, 0, 0, 1}));
    KMPMatcher literal("aba");
    KMPMatcher viewed(string_view("aba"));
    vector<long long> values = {LLONG_MIN, -1, 0, 256, LLONG_MAX};
    for (int tc = 0; tc < 3000; ++tc) {
        vector<long long> text(rng() % 80), pattern(rng() % 12);
        for (auto &v : text) v = values[rng() % values.size()];
        for (auto &v : pattern) v = values[rng() % values.size()];
        check_sequence(text, pattern, rng);
        if (!text.empty()) {
            size_t l = rng() % text.size(), r = l + rng() % (text.size() - l + 1);
            check_sequence(text, vector<long long>(text.begin() + l, text.begin() + r), rng);
        }
    }
    vector<int> integers(1000);
    iota(integers.begin(), integers.end(), -500);
    check_sequence(integers, vector<int>(integers.begin() + 256, integers.end()), rng);
    check_sequence(vector<int>{1, -2, 1, -2, 1}, vector<int>{1, -2, 1}, rng);
    check_sequence(vector<Token>{{1}, {2}, {1}, {2}, {1}}, vector<Token>{{1}, {2}, {1}}, rng);
    check_sequence(vector<string>{"cat", "dog", "cat"}, vector<string>{"cat"}, rng);
    list<int> streamed = {1, 2, 1, 2, 1};
    KMPMatcher integer_owned(vector<int>{1, 2, 1});
    vector<long long> result;
    integer_owned.scan(streamed.begin(), streamed.end(), [&](long long p) { result.push_back(p); });
    assert(result == vector<long long>({0, 2}));
}
