#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../string/suffix_automaton.cpp"

template<int W>
void check(const string &s, const SuffixAutomaton<W> &sam) {
    set<string> substrings;
    for (int l = 0; l < (int)s.size(); ++l) {
        for (int r = l + 1; r <= (int)s.size(); ++r) substrings.insert(s.substr(l, r - l));
    }
    assert(sam.count_distinct_substrings() == (long long)substrings.size());
    assert(!sam.kth_substring(-1));
    assert(!sam.kth_substring(LLONG_MIN));
    assert(!sam.kth_substring(substrings.size()));
    assert(!sam.kth_substring(LLONG_MAX));
    long long k = 0;
    for (const auto &expected : substrings) {
        auto range = sam.kth_substring(k++);
        assert(range);
        auto [l, r] = *range;
        assert(0 <= l && l < r && r <= (int)s.size());
        assert(s.substr(l, r - l) == expected);
        assert(sam.kth_substring(k - 1) == range);
    }
}

int main() {
    for (int n = 0; n <= 9; ++n) for (int mask = 0; mask < (1 << n); ++mask) {
        string s(n, 'a');
        for (int i = 0; i < n; ++i) s[i] += (mask >> i) & 1;
        SuffixAutomaton<2> sam(s);
        check(s, sam);
        sam.build(string());
        check(s, sam);
        sam.add('b');
        s += 'b';
        check(s, sam);
        auto copy = sam;
        copy.build(string("aba"));
        check(s + "aba", copy);
        check(s, sam);
    }
    mt19937 rng(233);
    for (int tc = 0; tc < 300; ++tc) {
        SuffixAutomaton<3> sam;
        string s;
        for (int step = 0; step < 15; ++step) {
            check(s, sam);
            char c = 'a' + rng() % 3;
            sam.add(c);
            s += c;
        }
        check(s, sam);
    }
    string s(100000, 'a');
    for (char &c : s) c += rng() % 3;
    SuffixAutomaton<3> sam(s);
    long long total = sam.count_distinct_substrings();
    assert(total > INT_MAX);
    assert(sam.kth_substring(0));
    assert(sam.kth_substring(total - 1));
    assert(!sam.kth_substring(total));
}
