#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../string/suffix_array.cpp"
#include "../string/suffix_array.cpp"

template<class Sequence, class Pattern>
void check(const SuffixArray<Sequence>& index, const Pattern& pattern,
           const vector<int>& values, const vector<int>& target) {
    const auto& sa = index.array();
    int l = 0, r = 0;
    vector<int> expected;
    for (int pos = 0; pos < (int)values.size(); ++pos) {
        vector<int> prefix(values.begin() + pos,
                           values.begin() + pos + min(values.size() - pos, target.size()));
        l += prefix < target;
        r += prefix <= target;
        if (prefix == target) expected.push_back(pos);
    }
    auto result = index.equal_range(pattern);
    assert(result == make_pair(l, r));
    vector<int> actual(sa.begin() + result.first, sa.begin() + result.second);
    sort(actual.begin(), actual.end());
    assert(actual == expected);
}

void check_patterns(const vector<int>& values, const vector<vector<int>>& patterns) {
    const SuffixArray sa(values);
    assert(sa.array() == suffix_array(values));
    assert(sa.size() == (int)values.size());
    vector<int> expected_lcp;
    for (int i = 1; i < sa.size(); ++i) {
        int a = sa[i - 1], b = sa[i], common = 0;
        while (a + common < sa.size() && b + common < sa.size()
               && values[a + common] == values[b + common]) ++common;
        expected_lcp.push_back(common);
    }
    assert(sa.lcp() == expected_lcp);
    for (const auto& pattern : patterns) check(sa, pattern, values, pattern);
    string text;
    for (int x : values) text += char(x);
    const SuffixArray byte_sa(text);
    assert(byte_sa.array() == suffix_array(text));
    assert(byte_sa.lcp() == lcp(text, byte_sa.array()));
    vector<int> bytes;
    for (unsigned char c : text) bytes.push_back(c);
    for (const auto& pattern : patterns) {
        string p;
        vector<int> target;
        for (int x : pattern) {
            p += char(x);
            target.push_back((unsigned char)p.back());
        }
        check(byte_sa, p, bytes, target);
        string wrapped = "x" + p + "y";
        check(byte_sa, string_view(wrapped).substr(1, p.size()), bytes, target);
    }
}

vector<vector<int>> words(int max_length) {
    vector<vector<int>> result(1);
    for (size_t i = 0; i < result.size(); ++i) {
        if ((int)result[i].size() == max_length) continue;
        for (int c : {0, 128, 255}) {
            auto next = result[i];
            next.push_back(c);
            result.push_back(move(next));
        }
    }
    return result;
}

int main() {
    string original = "banana";
    const SuffixArray owned(original);
    original.assign("changed");
    assert(owned.equal_range("ana") == make_pair(1, 3));
    auto copied = owned;
    const auto moved = move(copied);
    assert(moved.array() == owned.array());
    assert(moved.equal_range("ana") == owned.equal_range("ana"));
    assert(SuffixArray("banana").equal_range("ana") == make_pair(1, 3));
    assert(SuffixArray(string("banana")).equal_range("ana") == make_pair(1, 3));
    vector<int> input{2, -1, 2, -1};
    const SuffixArray numbers(input);
    input.clear();
    assert(numbers.equal_range(vector<int>{-1}) == make_pair(0, 2));
    auto patterns = words(4);
    for (const auto& text : words(5)) check_patterns(text, patterns);
    vector<int> runs(192, 128);
    runs[48] = 255;
    runs[96] = 0;
    runs[144] = 255;
    vector<vector<int>> long_patterns;
    for (int length : {1, 47, 48, 49, 96, 193}) {
        for (int last : {0, 127, 128, 129, 255}) {
            vector<int> pattern(length, 128);
            pattern.back() = last;
            long_patterns.push_back(move(pattern));
        }
    }
    check_patterns(runs, long_patterns);
    check_patterns({INT_MIN, -1, INT_MAX, INT_MIN, 0},
                   {{}, {INT_MIN}, {-1, INT_MAX}, {INT_MAX, INT_MIN, 0}, {INT_MAX, INT_MAX}});
    mt19937 rng(304);
    for (int trial = 0; trial < 300; ++trial) {
        vector<int> text(rng() % 65);
        for (int& x : text) x = int(rng() % 9) - 4;
        vector<vector<int>> patterns(1);
        for (int pos = 0; pos < (int)text.size(); ++pos)
            patterns.emplace_back(text.begin() + pos, text.end());
        for (int i = 0; i < 20; ++i) {
            vector<int> p(rng() % 75);
            for (int& x : p) x = int(rng() % 9) - 4;
            patterns.push_back(move(p));
        }
        check_patterns(text, patterns);
    }
}
