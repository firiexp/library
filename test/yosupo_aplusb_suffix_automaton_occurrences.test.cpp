#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../string/suffix_automaton.cpp"

void check(const string &s, const SuffixAutomaton<2> &sam) {
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
        for (char c : {'b', 'a', 'b'}) {
            s += c;
            sam.add(c);
            check(s, sam);
        }
    }
}

int main() {
    self_check();
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
