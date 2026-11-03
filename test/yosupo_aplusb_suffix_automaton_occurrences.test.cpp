#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../string/suffix_automaton.cpp"

template<int W>
void check_distinct(const string &s, const SuffixAutomaton<W> &sam) {
    set<string> expected;
    for (int l = 0; l < (int)s.size(); ++l)
        for (int r = l + 1; r <= (int)s.size(); ++r)
            expected.insert(s.substr(l, r - l));
    long long total = 0;
    for (int v = 1; v < (int)sam.nodes.size(); ++v)
        total += sam.nodes[v].len - sam.nodes[sam.nodes[v].link].len;
    assert(sam.count_distinct_substrings() == (long long)expected.size());
    assert(sam.count_distinct_substrings() == total);
}

void check(const string &s, const SuffixAutomaton<2> &sam) {
    check_distinct(s, sam);
    auto before = sam.nodes;
    auto counts = sam.substring_occurrences();
    assert(counts == sam.substring_occurrences());
    assert(counts.size() == before.size());
    assert(counts[0] == (int)s.size());
    vector<bool> visited(counts.size());
    for (int l = 0; l < (int)s.size(); ++l) {
        int v = 0;
        for (int r = l; r < (int)s.size(); ++r) {
            v = sam.nodes[v].next[s[r] - 'a'];
            assert(v > 0);
            int expected = 0;
            for (int start = 0; start + r - l < (int)s.size(); ++start)
                expected += s.compare(start, r - l + 1, s, l, r - l + 1) == 0;
            assert(counts[v] == expected);
            visited[v] = true;
        }
    }
    for (int v = 0; v < (int)before.size(); ++v) {
        assert(v == 0 || visited[v]);
        assert(sam.nodes[v].link == before[v].link);
        assert(sam.nodes[v].len == before[v].len);
        assert(sam.nodes[v].occ == before[v].occ);
        assert(equal(begin(sam.nodes[v].next), end(sam.nodes[v].next), begin(before[v].next)));
    }
}

void self_check() {
    for (int n = 0; n <= 10; ++n) for (int mask = 0; mask < (1 << n); ++mask) {
        string s(n, 'a');
        for (int i = 0; i < n; ++i) s[i] += (mask >> i) & 1;
        SuffixAutomaton<2> sam(s);
        check(s, sam);
        SuffixAutomaton<2> online;
        check_distinct("", online);
        for (int i = 0; i < n; ++i) {
            online.add(s[i]);
            check_distinct(s.substr(0, i + 1), online);
        }
        SuffixAutomaton<2> chunks(s.substr(0, n / 2));
        chunks.build(s.substr(n / 2));
        chunks.build(string());
        check_distinct(s, chunks);
        for (char c : {'b', 'a', 'b'}) {
            s += c;
            sam.add(c);
            check(s, sam);
        }
    }
    mt19937 rng(311);
    string s(100000, 'a');
    for (char &c : s) c += rng() % 26;
    SuffixAutomaton<26> large(s);
    long long total = 0;
    for (int v = 1; v < (int)large.nodes.size(); ++v)
        total += large.nodes[v].len - large.nodes[large.nodes[v].link].len;
    assert(total > INT_MAX);
    assert(large.count_distinct_substrings() == total);
}

int main() {
    self_check();
}
