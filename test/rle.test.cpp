#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../util/rle.cpp"

template<class Sequence>
void check(const Sequence& input) {
    using T = typename Sequence::value_type;
    vector<pair<T, int>> runs = RLE(input);
    vector<T> restored;
    for (size_t i = 0; i < runs.size(); ++i) {
        assert(runs[i].second > 0);
        if (i) assert(runs[i - 1].first != runs[i].first);
        restored.insert(restored.end(), runs[i].second, runs[i].first);
    }
    assert(restored == vector<T>(input.begin(), input.end()));
}

int main() {
    for (const string& s : {string(), string("a"), string(1000, 'a'),
                           string("abababab"), string("a\0\0\x80\xff\xff", 6)}) {
        auto original = s;
        check(s);
        for (size_t l = 0; l <= s.size(); l += max(size_t(1), s.size() / 10)) {
            for (size_t r = l; r <= s.size(); r += max(size_t(1), s.size() / 10)) {
                string_view view(s.data() + l, r - l);
                check(view);
                assert(RLE(view) == RLE(string(view)));
            }
        }
        assert(s == original);
    }
    assert((RLE("aaabbc") == vector<pair<char, int>>{{'a', 3}, {'b', 2}, {'c', 1}}));
    check(vector<int>{});
    check(vector<int>{INT_MIN, INT_MIN, 0, INT_MAX, INT_MIN});
    check(vector<string>{"a", "a", "ab", ""});
    check(vector<bool>{true, true, false, true});
    mt19937 rng(309);
    for (int trial = 0; trial < 1000; ++trial) {
        string s(rng() % 201, '\0');
        for (char& c : s) c = char(rng() % (trial % 2 ? 256 : 3));
        check(s);
        size_t l = rng() % (s.size() + 1);
        check(string_view(s).substr(l, rng() % (s.size() - l + 1)));
    }
}
